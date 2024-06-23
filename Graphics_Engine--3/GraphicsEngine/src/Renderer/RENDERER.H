#ifndef RENDERER_H
#define RENDERER_H
#include "Exports/Exports.h"
#include "Window/Window.h"
#include "GLM/mat4x4.hpp"
#include "Shader/Shader.h"
#include "Vertex/Vertex.h"
#include "Texture2/Texture2.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

enum TypeShape {
	Triangle=3, Quad
};


typedef unsigned int uint;
static class GraficosEngine_API Renderer {
private:

	//Window* _window;
	Shader* _shader;
	glm::vec4 _clearColor;
	glm::mat4 _projection, _view;
	uint _uniformTransform;
	uint _uniformView;
	uint _uniformProjection;
	void Start();
	void InitShader();
public:
	glm::mat4 GetView() { return _view; }
	glm::mat4 GetProjection() { return _projection; }
	//----- C y D -------
	Renderer();
	~Renderer();
	void Init();
	void SetDepth();
	// --------------------
	void UseShader();
	uint GetShaderId();
	void CleanShader();
	void GenBuffers(uint& VAO, uint& VBO, uint& EBO);
	void GenBuffers(uint& VAO, uint& VBO, uint& EBO, uint& UVB);
	//void BindBuffer(uint VAO, uint VBO, int tam, float* vertices);
	void BindBuffer(uint VAO, uint VBO, int tam, const void* vertices);
	void SetBaseAttribs(uint location, int size, int stride, int offset);
	void SetBaseAttribs(uint location, int size, GLsizei stride, const void* offset);
	void SetTextureAttribs(uint location, int size, int stride, int offset);
	void UpdateMVP(glm::mat4 model);
	void UpdateModel(glm::mat4 model);
	void UpdateVec3(uint uniformVec3, glm::vec3 vec3Value);
	void UpdateColor(uint uniformBaseColor, uint uniformAlpha, glm::vec4 baseColor);
	void UpdateColor(uint uniformBaseColor, glm::vec3 baseColor);
	void UpdateBoolValue(uint uniformStatus, bool status);
	void UpdateTexture(uint uniformTexture, uint textureId);
	void UpdateFloatValue(uint uniformFloat, float value);
	void UpdateInt(uint uniformInt, int value);
	void SetView(glm::mat4 view);
	void SetProjection(glm::mat4 projection);
	void DrawMesh(uint VAO, std::vector<unsigned int> indices);
	void Draw(uint VAO, uint VBO, uint& EBO, uint vertices, uint tamVerts, float* vertexs);
	void Draw(uint VAO, uint vertices);
	void DrawLines(uint VAO, uint vertices);
	void ClearScreen();
	void PostRender(Window* window);
	void CleanTexture();
	void UseTexture(bool v);
	void UseMaterial(bool v);
	void UseTexture(int number, uint id);
	void TextureEnable(uint textureId);
	void TextureEnableDiffuse(uint textureId);
	void TextureEnableSpecular(uint textureId);
	void BindTexture(uint textureId);
	void TextureDisable();
	void TextureActive();
	void TextureActive(int x);
	void TextureDelete(uint uniformTexture, uint& textureId);
	void BlendEnable();
	void BlendDisable();
	void BindIndexes(uint& EBO, int tam, uint* indexs);
	void BindUV(uint UVB, int tam, float* vertices);
	void reBindBuffer(uint UVB, int tam, const void* vertices);
	void UnBind(uint& VAO, uint& VBO, uint& EBO);
	void UnBind(uint& VAO, uint& VBO, uint& EBO, uint& UVB);
	void SetLocation(uint& location, const char* loc);
	void SetUniform(uint& uniform, const char* loc);
	void SetBackgroundColor(glm::vec4 color);
	void SetLight(uint uColor, uint uPos, uint uAmbient, glm::vec3 colorLight, glm::vec3 posLight, float ambient);
	void drawMesh(std::vector<MikkaiEngine::Vertex> vertices, std::vector<unsigned int> indices, std::vector<MikkaiEngine::Texture> textures, unsigned int VAO, glm::vec3 color);
	Shader* GetShader() { return _shader; }
};
#endif