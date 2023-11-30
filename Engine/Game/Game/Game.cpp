#include "Game.h"
#include "Timer/Timer.h"

Game::Game()
{
	player = nullptr;
	tallGrass = nullptr;
	grass = nullptr;
	idle = nullptr;
	up = nullptr;
	down = nullptr;
	left = nullptr;
	right = nullptr;
	time = 0;
}

Game::~Game()
{
	if (player != nullptr) {
		player = nullptr;
		delete player;
	}

	if (tallGrass != nullptr) {
		tallGrass = nullptr;
		delete tallGrass;
	}

	if (grass != nullptr) {
		grass = nullptr;
		delete grass;
	}

	if (idle != nullptr) {
		idle = nullptr;
		delete idle;
	}

	if (up != nullptr) {
		up = nullptr;
		delete up;
	}

	if (down != nullptr) {
		down = nullptr;
		delete down;
	}

	if (left != nullptr) {
		left = nullptr;
		delete left;
	}

	if (right != nullptr) {
		right = nullptr;
		delete right;
	}
}

void Game::Start()
{
	grass = new Sprite(renderer, "res/grass.png");
	grass->SetColor(glm::vec3(1, 1, 1));
	grass->SetPosition(400, 400, 0);
	grass->SetScale(800, 800, 100);

	tallGrass = new Sprite(renderer, "res/tallgrass.png");
	tallGrass->SetColor(glm::vec3(1, 1, 1));
	tallGrass->SetPosition(400, 400, 0);
	tallGrass->SetScale(100, 100, 100);

	player = new Sprite(renderer, "res/Sonic_Mania_Sprite_Sheet.png");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(400, 200, 0);
	player->SetScale(100, 100, 100);

	idle = new Animation();
	up = new Animation();
	down = new Animation();
	right = new Animation();
	left = new Animation();

	up->AddFrame(848, 203, 122 / 3, 48, 830, 465, 1000, 3);
	down->AddFrame(848, 203, 122 / 3, 48, 830, 465, 1000, 3);
	right->AddFrame(848, 203, 122 / 3, 48, 830, 465, 1000, 3);
	left->AddFrame(848, 203, 122 / 3, 48, 830, 465, 1000, 3);

	player->SetAnimation(up);

	//idleAnimation = new Animation();
	//idleAnimation->AddFrame(390, 98, 98 / 3, 43, 830, 465, 2500, 3);

	//idleAnimationCartel = new Animation();
	//idleAnimationCartel->AddFrame(133, 150, 49.5, 100, 832, 830, 465, 4);

	player->SetCollider(true);
	tallGrass->SetCollider(true);
}

void Game::Update()
{
	glm::vec3 lastPosition = player->GetPosition();

	if (IsKeyPressed(KEY_W))
	{
		player->Translate(0, 5, 0);
		player->SetAnimation(up);
	}
	else if (IsKeyPressed(KEY_S))
	{
		player->Translate(0, -5, 0);
		player->SetAnimation(down);
	}
	else if (IsKeyPressed(KEY_A))
	{
		player->Translate(-5, 0, 0);
		player->SetAnimation(left);
	}
	else if (IsKeyPressed(KEY_D))
	{
		player->Translate(5, 0, 0);
		player->SetAnimation(right);
	}
	else
	{
		player->SetAnimation(idle);
	}

	if (CollisionManager::CheckCollision(player, tallGrass))
	{
		player->SetPosition(lastPosition.x, lastPosition.y, lastPosition.z);
	}

	player->UpdateAnimation();
	grass->Draw();
	tallGrass->Draw();
	player->Draw();
}

void Game::End()
{
	delete player;
	delete tallGrass;
	delete grass;
}