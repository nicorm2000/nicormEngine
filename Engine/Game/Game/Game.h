#pragma once

#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:
	Sprite* player;
	Shape* shape = nullptr;
	glm::vec3 red = { 1, 0, 0 };

public:
	Game();
	~Game();

	void Start()override;
	void Update()override;
	void End()override;
};