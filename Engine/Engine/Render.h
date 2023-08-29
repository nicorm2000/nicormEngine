#pragma once
#include "Window.h"
#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Render
{
private:
	
public:
	static ShaderProgramSource ParseShader(const std::string& filePath);
	void ClearScreen();

	void PostRender(GLFWwindow* window);
	void DrawTriangle(float x, float y);
	static unsigned int CompilerShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void DeleteShader();
};