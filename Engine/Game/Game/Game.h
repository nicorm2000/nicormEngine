#pragma once

#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:
	Sprite* player;
	Sprite* grass;
	Sprite* tallGrass;
	Animation* idle;
	Animation* up;
	Animation* down;
	Animation* left;
	Animation* right;

	float time;

public:
	Game();
	~Game();

	void Start()override;
	void Update()override;
	void End()override;
};