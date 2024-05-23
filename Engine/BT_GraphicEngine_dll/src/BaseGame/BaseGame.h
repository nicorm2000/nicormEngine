#ifndef BASEGAME_H
#define BASEGAME_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <stdlib.h>
#include <Time.h>
#include "Renderer/Renderer.h"
#include "Camera/Camera.h"
#include "Input/Input.h"
#include "Timer/Timer.h"
#include "CollisionManager/CollisionManager.h"
#include "OcclusionCulling/OcclusionCulling.h"
#include "Material/MaterialManager.h"
#include "BSP/BSP.h"
using namespace std;

class DllApi BaseGame
{
protected:
	Window* window;
	Renderer* renderer;
	Camera* camera;

	virtual void Begin() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;

public:
	BaseGame();
	~BaseGame();
	void Run();
};

#endif