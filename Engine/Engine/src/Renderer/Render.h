#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Material/Material.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Export.h"

class DllApi Render
{
private:
	Window* window;
	Material* material;

	glm::mat4 view;
	glm::mat4 projection;

public:
	Render(Window* window);
	~Render();

	void SetDepth();

	void RotateCamera(glm::vec3 pos);

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
};

#endif