#ifndef BASEGAME_H
#define BASEGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Renderer/Render.h"
#include "Input/Input.h"
#include "Shape/Shape.h"
#include "Export.h"

class DllApi BaseGame
{
private:
	Window* window;
	Input* input;

protected:
	Render* renderer;

public:
	BaseGame();
	~BaseGame();

	int Run();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

	bool IsKeyPressed(int keycode);
	bool IsKeyDown(int keycode);
};

#endif