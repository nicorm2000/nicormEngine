#ifndef WINDOW_H
#define WINDOW_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <iostream>
using namespace std;

class DllApi Window
{
private:

	GLFWwindow* window;

	float height;
	float width;

public:
	Window(float width, float height);
	~Window();


	int InitLibrary();
	int CreateWindow();
	void MakeWindowContextCurrent();
	bool WindowShouldClose();
	void PollEvents();
	void TerminateLibrary();

	GLFWwindow* GetWindow();
	float GetHeight();
	float GetWidth();
};

#endif