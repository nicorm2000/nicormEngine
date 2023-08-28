#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window.h"

class Window
{
private:
	int width = 640;
	int height = 480;
	const char* title = "Engine";
	GLFWwindow* glfwWindow;

public:
	int InitWindow();
	int WindowChecker();

	void CloseWindow();
	void MakeCurrentContext(GLFWwindow* glfwWindow);
};