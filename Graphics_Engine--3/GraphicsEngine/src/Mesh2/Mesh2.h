#ifndef MESH2_H
#define MESH2_H

#include "Vertex/Vertex.h"
#include "Texture2/Texture2.h"
#include "Exports/Exports.h"
#include "Renderer/Renderer.h"
#include "Color/color.h"
#include <vector>
#include <Material/Material.h>


namespace MikkaiEngine
{
    class GraficosEngine_API Mesh {
    public:
		Mesh();
		Mesh(Renderer* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures);
		~Mesh();

		void Init();
		void Draw();
		void DeInit();

		MikkaiEngine::Material* material;
		Color color;

		void SetUniforms();
		void UpdateShader();

		Renderer* render;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;
		uint VAO, VBO, EBO;

		uint uniformColor;
		uint uniformAlpha;
		uint uniformBaseTexture;
		uint uniformUseTexture;

		uint locationPosition;
		uint locationNormal;
		uint locationTexCoord;
    };
}

#endif