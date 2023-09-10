#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"

class DllApi Window
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

#endif