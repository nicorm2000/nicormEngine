#ifndef WINDOW_H
#define WINDOW_H
#include "../Exports/Exports.h"
#include <iostream>

class GraficosEngine_API Window {
private:
	GLFWwindow* _window;
	int _width,_height;
	int MakeWindow(int w, int h, std::string name);
public:
	Window();
	Window(int w, int h, std::string name);

	void Start();

	// --------------------
	
	GLFWwindow* GetWindow();
	void ResizeWindow(int width, int height);
	int GetHeight(); int GetWidth();
};
#endif