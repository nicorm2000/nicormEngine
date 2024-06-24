#include "Importer2.h"
#include "Entity/Entity3D.h"
#include <TextureImporter/TextureImporter.h>
#include "MaterialManager/MaterialManager.h"
    
namespace MikkaiEngine
{
    Renderer* Importer2::render = nullptr;
    std::vector<Texture> Importer2::textures_loaded = std::vector<Texture>();
    std::string Importer2::directory = std::string();
    std::string assimpfbx = "$AssimpFbx$";

    Entity2* Importer2::LoadModel(Renderer* rend, std::string path)
    {
        render = rend;

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);// Read the model file using Assimp

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return nullptr;
        }

        directory = path.substr(0, path.find_last_of('/'));// Extract the directory from the path
        textures_loaded.clear();// Clear previously loaded textures

        Entity2* model = new Entity2(render);
        model->Init();
        model->setName(scene->mRootNode->mName.C_Str());

        ProcessNode(model, glm::mat4(1.f), scene->mRootNode, scene);// Recursively process the root node and its children

        return model;
    }

    void Importer2::ProcessNode(Entity2* parent, glm::mat4 mat, aiNode* node, const aiScene* scene)
    {
        Entity2* entityNode = nullptr;
        std::string name = node->mName.C_Str();

        if (name.find("$AssimpFbx$") != std::string::npos)// Check for Assimp-specific FBX transformation pivots
        {
            entityNode = parent;

            if (name.find("RotationPivot") != std::string::npos && name.find("Inverse") == std::string::npos)// Handle RotationPivot nodes
            {
                aiMatrix4x4 matrix = node->mTransformation;

                mat[0][0] = (float)matrix.a1; mat[0][1] = (float)matrix.b1;  mat[0][2] = (float)matrix.c1; mat[0][3] = (float)matrix.d1;
                mat[1][0] = (float)matrix.a2; mat[1][1] = (float)matrix.b2;  mat[1][2] = (float)matrix.c2; mat[1][3] = (float)matrix.d2;
                mat[2][0] = (float)matrix.a3; mat[2][1] = (float)matrix.b3;  mat[2][2] = (float)matrix.c3; mat[2][3] = (float)matrix.d3;
                mat[3][0] = (float)matrix.a4; mat[3][1] = (float)matrix.b4;  mat[3][2] = (float)matrix.c4; mat[3][3] = (float)matrix.d4;
            }
            if (name.find("Pivot") == std::string::npos)// Apply transformations for non-Pivot nodes
            {
                glm::mat4 m;
                aiMatrix4x4 matrix = node->mTransformation;

                m[0][0] = (float)matrix.a1; m[0][1] = (float)matrix.b1;  m[0][2] = (float)matrix.c1; m[0][3] = (float)matrix.d1;
                m[1][0] = (float)matrix.a2; m[1][1] = (float)matrix.b2;  m[1][2] = (float)matrix.c2; m[1][3] = (float)matrix.d2;
                m[2][0] = (float)matrix.a3; m[2][1] = (float)matrix.b3;  m[2][2] = (float)matrix.c3; m[2][3] = (float)matrix.d3;
                m[3][0] = (float)matrix.a4; m[3][1] = (float)matrix.b4;  m[3][2] = (float)matrix.c4; m[3][3] = (float)matrix.d4;

                mat *= m;
            }
        }
        else
        {
            // Create a new entity for nodes that are not Assimp FBX pivots
            entityNode = new Entity2(render);
            aiMatrix4x4 matrix = node->mTransformation;
            glm::mat4 m;

            m[0][0] = (float)matrix.a1; m[0][1] = (float)matrix.b1;  m[0][2] = (float)matrix.c1; m[0][3] = (float)matrix.d1;
            m[1][0] = (float)matrix.a2; m[1][1] = (float)matrix.b2;  m[1][2] = (float)matrix.c2; m[1][3] = (float)matrix.d2;
            m[2][0] = (float)matrix.a3; m[2][1] = (float)matrix.b3;  m[2][2] = (float)matrix.c3; m[2][3] = (float)matrix.d3;
            m[3][0] = (float)matrix.a4; m[3][1] = (float)matrix.b4;  m[3][2] = (float)matrix.c4; m[3][3] = (float)matrix.d4;
            m *= mat;
            
            entityNode->setName(name);
            if (node->mNumMeshes > 0)// If the node has meshes, process them
            {
                std::vector<Mesh*> meshes = std::vector<Mesh*>();
                for (uint i = 0; i < node->mNumMeshes; i++)
                {
                    aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
                    meshes.push_back(ProcessMesh(aiMesh, scene));// Process each mesh
                }
                entityNode->SetMeshes( meshes);
                entityNode->SetMatrix(m);
            }
            else// Handle nodes without meshes
            {
                entityNode = new Entity2(render);
                entityNode->setName(name + "pivot");
                entityNode->SetMatrix(m);
            }
        }

        for (uint i = 0; i < node->mNumChildren; i++)// Recursively process all children of the node
        {
            ProcessNode(entityNode, mat, node->mChildren[i], scene);
        }
        if (entityNode != nullptr)
        {
            entityNode->Init();
        }

        if (name.find("$AssimpFbx$") == std::string::npos)// Add the entity node to its parent if it's not an Assimp-specific FBX pivot
        {
            parent->AddChildren(entityNode);
            entityNode->setName(name);
            entityNode->SetParent(parent);

            entityNode->Init();
        }
    }


    Mesh* Importer2::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)// Process vertices
        {
            Vertex vertex;
            glm::vec3 vector;
            // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // Positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // Normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // Texture coordinates
            if (mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }
        // Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);// Add the face's indices to the indices vector
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];// Process material

        std::vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "base_color");
        textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        std::vector<Texture> metalnessMaps = LoadMaterialTextures(material, aiTextureType_METALNESS, "metalness");
        textures.insert(textures.end(), metalnessMaps.begin(), metalnessMaps.end());
        std::vector<Texture> diffuseRoughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "diffuse_roughness");
        textures.insert(textures.end(), diffuseRoughnessMaps.begin(), diffuseRoughnessMaps.end());
        std::vector<Texture> ambientOcclusionMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "ambient_occlusion");
        textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());

        aiColor4D color(0.f, 0.f, 0.f, 0.f);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);

        Material* mat = nullptr;
        if (textures.size() > 0)
        {
            mat = MaterialManager::GetTextureMaterial();
        }
        else
        {
            mat = MaterialManager::GetSolidMaterial();
        }

        // Create a mesh and process it with its corresponding color and material
        Mesh* m = new Mesh(render,vertices, indices, textures);
        m->Init();
        m->color = Color(color.r, color.g, color.b);
        m->material = mat;

        return m;
    }

    std::vector<Texture> Importer2::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        // Checks all material textures of a given type and loads the textures if they're not loaded yet. The required info is returned as a Texture struct.
        std::vector<Texture> textures;
        uint texturesCount = mat->GetTextureCount(type);

        for (uint i = 0; i < texturesCount; i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);// Get the texture filepath

            bool skip = false;
            for (uint j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);// Use the loaded texture if there is a texture already loaded
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {
                // Load and store the texture if not already loaded
                std::string path = directory + '/' + str.C_Str();
                Texture texture = TextureImporter::LoadTexture(path.c_str(), true);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        // Return all loaded textures
        return textures;
    }
}
