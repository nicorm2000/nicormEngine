#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Shader/Shader.h"
#include "Material/Material.h"
#include "Color/Color.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Export.h"

class DllApi Render
{
private:
	Shader* shader;

	Window* window;
	Material* material;

	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraF;
	glm::vec3 cameraUp;
	glm::vec3 cameraP;

	float yaw;
	float pitch;
	float sensitivity;
	float fov;

public:
	Render(Window* window);
	~Render();

	void SetDepth();

	void UpdateCameraPos(glm::vec3 pos);
	void UpdateProjection();
	void UpdateDirection();
	void SetYaw(float yaw);
	void SetPitch(float pitch);
	float GetYaw();
	float GetPitch();
	void SetSensitivity(float sensitivity);
	float GetSensitivity();
	void SetFront(glm::vec3 front);
	glm::vec3 GetFront();
	void SetUp(glm::vec3 up);
	glm::vec3 GetUp();
	void SetFOV(float fov);
	float GetFOV();

	void SetView(glm::mat4 view);
	void SetProjection(glm::mat4 projection);

	void ClearScreen();
	void ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SwapBuffers(GLFWwindow* window);

	int InitGLEW();
	void InitMaterial();

	void CreateBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void BindBuffers(GLsizeiptr sizeVertices, GLsizeiptr sizeIndices, const GLvoid* vertices, const GLvoid* indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void EnableVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);

	void BindTexture(GLenum target, GLuint texture);

	void DrawWithoutIndexBuffer(GLenum primitive, GLint offset, GLsizei count);
	void DrawWithIndexBuffer(GLenum primitive, GLsizei count, GLenum type, const GLvoid* indices, unsigned int& VAO);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	Material* GetMaterial();



	void UseShader();
	unsigned int GetShaderId();
	void CleanShader();

	void GenBuffers(unsigned int& VAO, unsigned int& VBO);
	void GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB);
	void BindBuffer(unsigned int VAO, unsigned int VBO, int tam, const void* vertices);
	void BindIndexs(unsigned int EBO, int tam, unsigned int* indexs);
	void BindUV(unsigned int UVB, int tam, float* vertices);
	void UnBind(unsigned int& VAO, unsigned int& VBO);
	void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB);

	void SetLocation(unsigned int& location, const char* loc);
	void SetUniform(unsigned int& uniform, const char* loc);
	void SetBaseAttribs(unsigned int location, int size, GLsizei stride, const void* offset);
	void SetTextureAttribs(unsigned int location, int size, int stride, int offset);

	void UpdateMVP(unsigned int uniformModel, unsigned int uniformView, unsigned int uniformProjection, glm::mat4 model);
	void UpdateVec3(unsigned int uniformVec3, glm::vec3 vec3Value);
	void UpdateColor(unsigned int uniformBaseColor, unsigned int uniformAlpha, glm::vec4 baseColor);
	void UpdateStatus(unsigned int uniformStatus, bool status);
	void UpdateLight(unsigned int uniformLight, glm::vec3 light);
	void UpdateTexture(unsigned int uniformTexture, unsigned int textureId);
	void UpdateFloatValue(unsigned int uniformFloat, float value);
	void UpdateIntValue(unsigned int uniformInt, int value);
	void UpdateCameraView(unsigned int uniformView, glm::vec3 position);
	void UpdateLightVec3(unsigned int uniformLightVec3, glm::vec3 light);
	void UpdateLightFloat(unsigned int uniformLightFloat, float value);
	void UpdateLightStatus(unsigned int uniformLightStatus, bool status);
	unsigned int GetUniform(unsigned int shaderId, const char* loc);

	void Draw(unsigned int VAO, unsigned int vertices);
	void DrawLines(unsigned int VAO, unsigned int vertices);

	void BindDiffuseMap(unsigned int textureId);
	void BindSpecularMap(unsigned int textureId);
	void TextureEnable();
	void TextureDisable();
	void TextureDelete(unsigned int uniformTexture, unsigned int& textureId);
	void BlendEnable();
	void BlendDisable();
	void UseTexture(int number, unsigned int id);
	void CleanTexture();

	Color clearColor;
};

#endif