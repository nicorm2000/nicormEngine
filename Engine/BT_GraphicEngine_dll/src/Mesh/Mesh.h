#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "TextureImporter/TextureImporter.h"
#include "Material/Material.h"
#include "Color/Color.h"
#include "Vertexs.h"
using namespace std;

class DllApi Mesh
{
private:
	void SetUniforms();
	void UpdateShader();

	Renderer* renderer;
	vector<Vertex> vertexs;
	vector<unsigned int> indexes;
	vector<Texture> textures;
	unsigned int VAO, VBO, EBO;

	unsigned int uniformColor;
	unsigned int uniformAlpha;
	unsigned int uniformBaseTexture;
	unsigned int uniformUseTexture;

	unsigned int locationPosition;
	unsigned int locationNormal;
	unsigned int locationTexCoord;

public:
	Mesh();
	Mesh(Renderer* renderer, vector<Vertex> vertexs, vector<unsigned int> indexes, vector<Texture> textures);
	~Mesh();

	void Init();
	void Draw();
	void DeInit();

	vector<Vertex> GetVertexs();

	Material* material;
	Color color;
};

#endif