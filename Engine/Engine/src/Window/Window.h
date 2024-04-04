#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"

class DllApi Window
{
private:
	GLFWwindow* window;
	int width = 0;
	int height = 0;
	const char* title = "Unicorm Engine";

public:
	Window(int width, int height);
	~Window();

	int InitLibrary();
	int CreateWindow();
	void MakeCurrentContext();
	bool WindowShouldClose();
	void PollEvents();
	void TerminateLibrary();

	GLFWwindow* GetWindow();

	int GetWidth();
	int GetHeight();
};

#endif