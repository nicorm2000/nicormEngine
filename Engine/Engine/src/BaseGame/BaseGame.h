#ifndef BASEGAME_H
#define BASEGAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Window/Window.h"
#include "Renderer/Render.h"
#include "Input/Input.h"
#include "CollisionManager/CollisionManager.h"
#include "Shape/Shape.h"
#include "Sprite/Sprite.h"
#include "Export.h"
#include "Camera/Camera.h"

class DllApi BaseGame
{
protected:
	Window* window;
	Input* input;
	CollisionManager* collisionManager;
	Camera* camera;
	Render* renderer;

public:
	BaseGame();
	~BaseGame();
	int Run();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;

	bool IsKeyPressed(int keycode);
	float GetFrameTime();
};

#endif