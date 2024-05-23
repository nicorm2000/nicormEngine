#pragma once

#include "BaseGame/BaseGame.h"
#include "Light/Light.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Light/SpotLight.h"

class Game : public BaseGame
{
private:
	Sprite* player;
	Sprite* bg;
	Sprite* sign;
	Animation* signIdle;
	Animation* idle;
	Animation* up;
	Animation* down;
	Animation* left;
	Animation* right;
	//DirectionalLight* directionalLight;
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