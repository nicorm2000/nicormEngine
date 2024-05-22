#pragma once

#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:
	Sprite* player;
	Sprite* grass;
	Sprite* sign;
	Animation* signIdle;
	Animation* idle;
	Animation* up;
	Animation* down;
	Animation* left;
	Animation* right;

	float time;
	float cameraSpeed;
	float cameraSpeedMultiplier;
	float deltaTime;
	float lastFrame;

	bool firstPerson;
	bool thirdPerson;

	glm::vec3 cameraPos;

public:
	Game();
	~Game();

	void Start()override;
	void Update()override;
	void End()override;
};