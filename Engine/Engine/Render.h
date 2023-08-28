#pragma once
#include "Window.h"

class Render
{
private:

public:
	void ClearScreen();

	void PostRender(GLFWwindow* window);
	void DrawTriangle(float x, float y);
};