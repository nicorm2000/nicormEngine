#pragma once
#include "Window.h"

class Renderer
{
private:

public:
	void ClearScreen();

	void PostRender(GLFWwindow* window);
};