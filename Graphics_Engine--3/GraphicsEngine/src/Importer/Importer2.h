#ifndef IMPORTER2_H
#define IMPORTER2_H
#define IMPORTER true
#include "Model/Model.h"
#include <STB/stb_image.h>
#include <ASSIMP/Importer.hpp>
#include <ASSIMP/postprocess.h>
#include <ASSIMP/scene.h>

namespace MikkaiEngine
{
	class GraficosEngine_API Importer2 {
	public:
		Importer2() {};
		~Importer2() {};

		static Entity2* LoadModel(Renderer* rend, std::string path);

	private:
		static Renderer* render;
		static std::string directory;
		static std::vector<Texture> textures_loaded;

		static void ProcessNode(Entity2* parent, glm::mat4 mat, aiNode* node, const aiScene* scene);
		static Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
		static std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	};
}



#endif