#ifndef PLAYER_H
#define PLAYER_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Input/Input.h"
#include "Entity3D/Entity3D.h"
#include "Timer/Timer.h"
using namespace std;

class DllApi Player : public Entity3D
{
private:
	Camera* camera;

	float moveBaseSpeed;
	float moveSpeed;
	float rotSpeed;

	void Inputs();
	float GetSpeedDelta();

public:
	Player();
	Player(Renderer* renderer);
	~Player();

	void Init(Camera* camera, float moveSpeed, float rotSpeed);
	void Update();
};

#endif