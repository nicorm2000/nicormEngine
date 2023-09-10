#ifndef RENDERER_H
#define RENDERER_H

#include "Window.h"
#include "Export.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class DllApi Render
{
private:
	Window* window;
public:
	Render(Window* window);
	~Render();
	static ShaderProgramSource ParseShader(const std::string& filePath);
	void ClearScreen();
	void ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void SwapBuffers(GLFWwindow* window);
	int InitGLEW();
	void CreateBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void BindBuffers(GLsizeiptr sizeVertices, GLsizeiptr sizeIndices, const GLvoid* vertices, const GLvoid* indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
	void EnableVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);
	void DrawWithoutIndexBuffer(GLenum primitive, GLint offset, GLsizei count);
	void DrawWithIndexBuffer(GLenum primitive, GLsizei count, GLenum type, const GLvoid* indices, unsigned int& VAO);

	/*void PostRender(GLFWwindow* window);
	void DrawTriangle(float x, float y);
	static unsigned int CompilerShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void DeleteShader();*/
};

#endif