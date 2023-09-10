#ifndef BASEGAME_H
#define BASEGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include "Render.h"
#include "Window.h"

class DllApi BaseGame
{
private:
	Window* window;
protected:
	Render* renderer;
public:
	BaseGame();
	~BaseGame();

	int Run();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
};

#endif