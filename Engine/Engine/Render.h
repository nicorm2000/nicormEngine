#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"
#include "Export.h"
#include "Material.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DllApi Render
{
private:
	Window* window;
	Material* material;
public:
	Render(Window* window);
	~Render();

	void ClearScreen();
	void ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SwapBuffers(GLFWwindow* window);

	int InitGLEW();
	void InitMaterial();

	void CreateBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void BindBuffers(GLsizeiptr sizeVertices, GLsizeiptr sizeIndices, const GLvoid* vertices, const GLvoid* indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void EnableVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);
	void DrawWithoutIndexBuffer(GLenum primitive, GLint offset, GLsizei count);
	void DrawWithIndexBuffer(GLenum primitive, GLsizei count, GLenum type, const GLvoid* indices, unsigned int& VAO);
	Material* GetMaterial();
};

#endif