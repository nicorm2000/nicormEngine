#pragma once
#include "Window.h"
#include <string>

class Render
{
private:

public:
	void ClearScreen();

	void PostRender(GLFWwindow* window);
	void DrawTriangle(float x, float y);
	static unsigned int CompilerShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};