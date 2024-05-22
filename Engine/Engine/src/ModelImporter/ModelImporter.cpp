//#include "ModelImporter.h"
//
//Renderer* ModelImporter::renderer = nullptr;
//vector<Texture> ModelImporter::textures_loaded = vector<Texture>();
//string ModelImporter::directory = string();
//string assimpfbx = "$AssimpFbx$";
//
//ModelImporter::ModelImporter()
//{
//}
//
//ModelImporter::~ModelImporter()
//{
//}
//
//Entity3D* ModelImporter::LoadModel(Renderer* render, string path)
//{
//    renderer = render;
//
//    // Se lee el archivo con ASSIMP
//    Assimp::Importer importer;
//    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
//
//    // Se chequean errores
//    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // Si no es cero
//    {
//        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//        return nullptr;
//    }
//
//    // Se recupera la ruta del directorio del archivo para acceder al mtl con las texturas
//    directory = path.substr(0, path.find_last_of('/'));
//    textures_loaded.clear();
//
//    Entity3D* model = new Entity3D(renderer);
//    model->Init();
//    model->name = scene->mRootNode->mName.C_Str();
//
//    // Se procesa el ASSIMP's root node recursivamente
//    ProcessNode(model, scene->mRootNode, scene);
//
//    return model;
//}
//
//void ModelImporter::ProcessNode(Entity3D* parent, aiNode* node, const aiScene* scene)
//{
//    Entity3D* entityNode = nullptr;
//    string name = node->mName.C_Str();
//
//    if (node->mNumMeshes > 0)
//    {
//        vector<Mesh*> meshes = vector<Mesh*>();
//
//        // Si hay meshes, las procesa todas
//        for (unsigned int i = 0; i < node->mNumMeshes; i++)
//        {
//            // El objeto del nodo solo contiene indeces para indexar las objetos reales en la escena
//            // La escena contiene todos los datos, el nodo es solo para manterner las cosas organizadas (como las relaciones entre los nodos)
//            aiMesh* aiMesh = scene->mMeshes[node->mMeshes[i]];
//            meshes.push_back(ProcessMesh(aiMesh, scene));
//        }
//
//        entityNode = new Entity3D(meshes, renderer);
//    }
//    else
//    {
//        entityNode = new Entity3D(renderer);
//    }
//
//    // Hace lo mismo para cada uno de los hijos
//    for (unsigned int i = 0; i < node->mNumChildren; i++)
//    {
//        ProcessNode(entityNode, node->mChildren[i], scene);
//    }
//
//    parent->AddNode(entityNode);
//    entityNode->name = name;
//    entityNode->SetParent(parent);
//    entityNode->Init();
//
//    glm::vec4 m1 = glm::vec4(node->mTransformation.a1, node->mTransformation.a2, node->mTransformation.a3, node->mTransformation.a4);
//    glm::vec4 m2 = glm::vec4(node->mTransformation.b1, node->mTransformation.b2, node->mTransformation.b3, node->mTransformation.b4);
//    glm::vec4 m3 = glm::vec4(node->mTransformation.c1, node->mTransformation.c2, node->mTransformation.c3, node->mTransformation.c4);
//    glm::vec4 m4 = glm::vec4(node->mTransformation.d1, node->mTransformation.d2, node->mTransformation.d3, node->mTransformation.d4);
//    glm::mat4 mat = glm::mat4(m1, m2, m3, m4);
//    entityNode->SetMatrix(mat);
//}
//
//Mesh* ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
//{
//    vector<Vertex> vertices;
//    vector<unsigned int> indices;
//    vector<Texture> textures;
//
//    // Reccore cada vertice de las meshes
//    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
//    {
//        Vertex vertex;
//
//        // Se declara un vector de posición ya que Assimp usa su propia clase de vector que no se convierte 
//        // directamente a la clase vec3 de glm, entonces primero transferimos los datos a este vector
//        glm::vec3 vector;
//
//        // Posiciones
//        vector.x = mesh->mVertices[i].x;
//        vector.y = mesh->mVertices[i].y;
//        vector.z = mesh->mVertices[i].z;
//        vertex.Position = vector;
//
//        // Normales
//        if (mesh->HasNormals())
//        {
//            vector.x = mesh->mNormals[i].x;
//            vector.y = mesh->mNormals[i].y;
//            vector.z = mesh->mNormals[i].z;
//            vertex.Normal = vector;
//        }
//
//        // Coordenadas de textura
//        if (mesh->mTextureCoords[0])
//        {
//            glm::vec2 vec;
//            vec.x = mesh->mTextureCoords[0][i].x;
//            vec.y = mesh->mTextureCoords[0][i].y;
//            vertex.TexCoords = vec;
//        }
//        else
//        {
//            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
//        }
//
//        vertices.push_back(vertex);
//    }
//
//    // Se recorre cada una de las caras de la mesh (una cara es una mesh y su triangulo) y se recuperan los vertex index correspondientes
//    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
//    {
//        aiFace face = mesh->mFaces[i];
//
//        // Se recuperan todos los indices de la cara y se almacenan en el vector de indices
//        for (unsigned int j = 0; j < face.mNumIndices; j++)
//        {
//            indices.push_back(face.mIndices[j]);
//        }
//    }
//
//    // Proceso de materiales
//    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
//
//    // Cada textura se nombra como 'texture_diffuseN' donde la N es un numero sequencial que va de 1 a MAX_SAMPLER_NUMBER
//    // diffuse: texture_diffuseN
//    // specular: texture_specularN
//    // normal: texture_normalN
//
//    //vector<Texture> baseColorMaps = LoadMaterialTextures(material, aiTextureType_BASE_COLOR, "base_color");
//    //textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());
//
//    // 1. Diffuse maps
//    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
//    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//    // 2. Specular maps
//    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
//    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//    // 3. Normal maps
//    vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
//    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
//    // 4. Height maps
//    vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
//    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
//
//    //vector<Texture> metalnessMaps = LoadMaterialTextures(material, aiTextureType_METALNESS, "metalness");
//    //textures.insert(textures.end(), metalnessMaps.begin(), metalnessMaps.end());
//    //vector<Texture> diffuseRoughnessMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE_ROUGHNESS, "diffuse_roughness");
//    //textures.insert(textures.end(), diffuseRoughnessMaps.begin(), diffuseRoughnessMaps.end());
//    //vector<Texture> ambientOcclusionMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT_OCCLUSION, "ambient_occlusion");
//    //textures.insert(textures.end(), ambientOcclusionMaps.begin(), ambientOcclusionMaps.end());
//
//    aiColor4D color(0.f, 0.f, 0.f, 0.f);
//    aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
//    Material* mat = nullptr;
//
//    if (textures.size() > 0)
//    {
//        mat = MaterialManager::GetTextureMaterial();
//    }
//    else
//    {
//        mat = MaterialManager::GetSolidMaterial();
//    }
//
//    Mesh* m = new Mesh(renderer, vertices, indices, textures);
//    m->color = Color(color.r, color.g, color.b, 1.f);
//    m->material = mat;
//
//    // Se devuelve un mesh object creado a partir de los datos extraidos de la mesh
//    return m;
//}
//
//vector<Texture> ModelImporter::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
//{
//    vector<Texture> textures;
//    unsigned int texturesCount = mat->GetTextureCount(type);
//
//    for (unsigned int i = 0; i < texturesCount; i++)
//    {
//        aiString str;
//        mat->GetTexture(type, i, &str);
//
//        // Se chequea si la textura ya se cargo antes
//        bool skip = false;
//        for (unsigned int j = 0; j < textures_loaded.size(); j++)
//        {
//            if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
//            {
//                textures.push_back(textures_loaded[j]);
//                skip = true; // si ya se cargo una textura con la misma ruta de archivo, continúa con la siguiente (optimizacion)
//                break;
//            }
//        }
//
//        // Si no fue cargada antes, se carga
//        if (!skip)
//        {
//            string path = directory + '/' + str.C_Str();
//            Texture texture = TextureImporter::LoadTexture(path.c_str(), true);
//            texture.type = typeName;
//            texture.path = str.C_Str();
//            textures.push_back(texture);
//            textures_loaded.push_back(texture);  // Lo guarda como textura cargada para todo el modelo, para asegurarse de no cargar texturas duplicadas
//        }
//    }
//    return textures;
//}