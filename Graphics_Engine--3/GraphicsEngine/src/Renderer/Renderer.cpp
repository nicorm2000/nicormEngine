#include "Renderer.h"
#include <iostream>
#include "GLM/gtc/type_ptr.hpp"
#include "Animation/Animation.h"


//-----C y D---------------------------
Renderer::Renderer() {
	_shader = nullptr;
	_view = glm::mat4(0.f);
	_projection = glm::mat4(0.f);
}
Renderer::~Renderer()
{
	if (_shader != nullptr)
	{
		delete _shader;
		_shader = nullptr;
	}
}
//-------------------------------------

void Renderer::Init()
{
	InitShader();
}

void Renderer::SetDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::UseShader()
{
	glUseProgram(GetShaderId());
}

uint Renderer::GetShaderId()
{
	return _shader->GetShaderId();
}
void Renderer::CleanShader()
{
	glUseProgram(0);
}

void Renderer::Start() {
	std::cout << "+Renderer" << std::endl;
	InitShader();
	_view = glm::lookAt(glm::vec3(0, 0, -100), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::InitShader()
{
	_shader = new Shader();
	_shader->CreateShader("Shaders/vertex.shader", "Shaders/fragment.shader");
	SetUniform(_uniformTransform, "model");
	SetUniform(_uniformView, "view");
	SetUniform(_uniformProjection, "projection");
}

void Renderer::GenBuffers(uint& VAO, uint& VBO, uint& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}
void Renderer::GenBuffers(uint& VAO, uint& VBO, uint& EBO,uint& UVB)
{
	GenBuffers(VAO, VBO, EBO);
	glGenBuffers(1, &UVB);
}
//void Renderer::BindBuffer(uint VAO, uint VBO, int tam, float* vertices)
//{
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
//}
void Renderer::BindBuffer(uint VAO, uint VBO, int tam, const void* vertices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
}
void Renderer::BindIndexes(uint& EBO, int tam, uint* indexs)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
}
void Renderer::BindUV(uint UVB, int tam, float* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVB);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_DYNAMIC_DRAW);
}
void Renderer::reBindBuffer(uint UVB, int tam, const void* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVB);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_DYNAMIC_DRAW);
}
void Renderer::UnBind(uint& VAO, uint& VBO, uint& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void Renderer::UnBind(uint& VAO, uint& VBO, uint& EBO, uint& UVB)
{
	UnBind(VAO, VBO, EBO);
	glDeleteBuffers(1, &UVB);
}
void Renderer::SetLocation(uint& location, const char* loc)
{
	location = glGetAttribLocation(GetShaderId(), loc);
}
void Renderer::SetUniform(uint& uniform, const char* loc)
{
	uniform = glGetUniformLocation(GetShaderId(), loc);
}
void Renderer::SetBackgroundColor(glm::vec4 color)
{
	_clearColor = color;
}
void Renderer::SetLight(uint uColor, uint uPos, uint uAmbient, glm::vec3 colorLight, glm::vec3 posLight, float ambient)
{
	UpdateVec3(uPos, posLight);
	UpdateVec3(uColor, colorLight);
	UpdateFloatValue(uAmbient, ambient);
}
void Renderer::drawMesh(std::vector<MikkaiEngine::Vertex> vertices, std::vector<unsigned int> indices, std::vector<MikkaiEngine::Texture> textures, unsigned int VAO, glm::vec3 color)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	unsigned int colorLoc = glGetUniformLocation(GetShaderId(), "color");
	glUniform3fv(colorLoc, 1, glm::value_ptr(color));

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
			name = "diffuse";
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
			name = "specular";
		}
		uint a;
		SetUniform(a,("material." + name + number).c_str());
		UpdateFloatValue(a, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Renderer::SetBaseAttribs(uint location, int size, int stride, int offset)
{
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(location);
}
void Renderer::SetBaseAttribs(uint location, int size, GLsizei stride, const void* offset)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
}
void Renderer::SetTextureAttribs(uint location, int size, int stride, int offset)
{
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
	glEnableVertexAttribArray(location);
}
void Renderer::UpdateMVP(glm::mat4 model)
{
	glUniformMatrix4fv(_uniformTransform, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(_uniformView, 1, GL_FALSE, glm::value_ptr(_view));
	glUniformMatrix4fv(_uniformProjection, 1, GL_FALSE, glm::value_ptr(_projection));
}
void Renderer::UpdateModel(glm::mat4 model)
{
	glUniformMatrix4fv(_uniformTransform, 1, GL_FALSE, glm::value_ptr(model));
}
void Renderer::UpdateVec3(uint uniformVec3, glm::vec3 vec3Value)
{
	glUniform3fv(uniformVec3, 1, glm::value_ptr(vec3Value));
}
void Renderer::UpdateColor(uint uniformBaseColor, uint uniformAlpha, glm::vec4 baseColor)
{
	glUniform3fv(uniformBaseColor, 1, glm::value_ptr(glm::vec3(baseColor.r, baseColor.g, baseColor.b)));
	glUniform1fv(uniformAlpha, 1, &(baseColor.a));
}
void Renderer::UpdateColor(uint uniformBaseColor, glm::vec3 baseColor)
{
	glUniform3fv(uniformBaseColor, 1, glm::value_ptr(glm::vec3(baseColor.r, baseColor.g, baseColor.b)));
	uint a;
	SetUniform(a,"a");
	UpdateFloatValue(a, 1);
}
void Renderer::UpdateBoolValue(uint uniformStatus, bool status)
{
	glUniform1i(uniformStatus, status);
}
void Renderer::UpdateTexture(uint uniformTexture, uint textureId)
{
	glUniform1f(uniformTexture, (GLfloat)textureId);
}
void Renderer::UpdateFloatValue(uint uniformFloat, float value)
{
	glUniform1f(uniformFloat, value);
}
void Renderer::UpdateInt(uint uniformInt, int value)
{
	glUniform1i(uniformInt, value);
}
void Renderer::SetView(glm::mat4 view)
{
	_view = view;
}
void Renderer::SetProjection(glm::mat4 projection)
{
	_projection = projection;
}
void Renderer::DrawMesh(uint VAO, std::vector<unsigned int> indices)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
void Renderer::Draw(uint VAO, uint VBO, uint& EBO, uint vertices, uint tamVerts, float* vertexs)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, tamVerts, vertexs, GL_STATIC_DRAW);
	glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Renderer::Draw(uint VAO, uint vertices)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Renderer::DrawLines(uint VAO, uint vertices)
{
	glBindVertexArray(VAO);

	glDrawArrays(GL_LINES, 0, vertices);

	glBindVertexArray(0);
}
//void Renderer::DrawMesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, unsigned int VAO)
//{
//	unsigned int diffuseNr = 1;
//	unsigned int specularNr = 1;
//	for (unsigned int i = 0; i < textures.size(); i++)
//	{
//		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
//		// retrieve texture number (the N in diffuse_textureN)
//		std::string number;
//		std::string name = textures[i].type;
//		if (name == "texture_diffuse")
//		{
//			number = std::to_string(diffuseNr++);
//			name = "diffuse";
//		}
//		else if (name == "texture_specular")
//		{
//			number = std::to_string(specularNr++);
//			name = "specular";
//		}
//
//		uint a = 0;
//		SetUniform(a, ("material." + name + number).c_str());
//
//		UpdateFloatValue(a, i);
//		glBindTexture(GL_TEXTURE_2D, textures[i].id);
//	}
//	glActiveTexture(GL_TEXTURE0);
//
//	// draw mesh
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//}
void Renderer::ClearScreen()
{
	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::PostRender(Window* window)
{
	glfwSwapBuffers(window->GetWindow());
	glfwPollEvents();
}
void Renderer::CleanTexture()
{
	glActiveTexture(GL_TEXTURE0);
}
void Renderer::UseTexture(bool v)
{
	uint a;
	SetUniform(a, "useTexture");
	UpdateBoolValue(a, v);
}
void Renderer::UseMaterial(bool v)
{
	uint a;
	SetUniform(a, "useMaterial");
	UpdateBoolValue(a, v);
}
void Renderer::UseTexture(int number, uint id)
{
	glActiveTexture(GL_TEXTURE0 + number);
	glBindTexture(GL_TEXTURE_2D, id);
}
void Renderer::TextureEnable(uint textureId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}
void Renderer::TextureEnableDiffuse(uint textureId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}
void Renderer::TextureEnableSpecular(uint textureId)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId);
}
void Renderer::BindTexture(uint textureId)
{
	glBindTexture(GL_TEXTURE_2D, textureId);
}
void Renderer::TextureDisable()
{
	glDisable(GL_TEXTURE_2D);
}
void Renderer::TextureActive()
{
	glActiveTexture(GL_TEXTURE0);
}
void Renderer::TextureActive(int x)
{
	glActiveTexture(GL_TEXTURE0+x);
}
void Renderer::TextureDelete(uint uniformTexture, uint& textureId)
{
	glDeleteTextures(uniformTexture, &textureId);
}
void Renderer::BlendEnable()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void Renderer::BlendDisable()
{
	glDisable(GL_BLEND);
}