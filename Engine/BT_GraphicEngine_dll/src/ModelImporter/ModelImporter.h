#ifndef MODELIMPORTER_H
#define MODELIMPORTER_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <vector>
#include "Entity3D/Entity3D.h"
#include "Mesh/Mesh.h"
#include "Material/MaterialManager.h"
#include "TextureImporter/TextureImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
using namespace std;

class DllApi ModelImporter
{
private:
	static Renderer* renderer;
	static string directory;
	static vector<Texture> textures_loaded;

	static void ProcessNode(Entity3D* parent, aiNode* node, const aiScene* scene);
	static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

public:
	ModelImporter();
	~ModelImporter();

	static Entity3D* LoadModel(Renderer* render, string path);
};

#endif