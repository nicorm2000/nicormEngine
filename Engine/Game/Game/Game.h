#pragma once

#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
private:
	Sprite* player;
	Sprite* player2;
	Sprite* grass;
	Sprite* tallGrass;
	Animation* idle;
	Animation* up;
	Animation* down;
	Animation* left;
	Animation* right;
	Animation* idle2;
	Animation* up2;
	Animation* down2;
	Animation* left2;
	Animation* right2;

	float time;

public:
	Game();
	~Game();

	void Start()override;
	void Update()override;
	void End()override;
};