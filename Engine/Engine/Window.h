#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"

class DllApi Window
{
private:
	GLFWwindow* glfwWindow;
	int width = 0;
	int height = 0;
	const char* title = "Engine";

public:
	Window(int width, int height);
	~Window();
	int InitLibrary();
	int CreateWindow();
	void PollEvents();
	bool WindowShouldClose();

	GLFWwindow* GetWindow();
	int GetWidth();
	int GetHeight();

	void CloseWindow();
	void MakeCurrentContext();
};

#endif