#include "Game.h"
#include "Timer/Timer.h"

Game::Game()
{
	player = nullptr;
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
	player = new Sprite(renderer, "res/SpriteSheet.png");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(0, 0, 0);
	player->SetScale(100, 100, 100);

	idle = new Animation();
	idle->AddFrame(8, 15, 16, 10, 160, 256);

	up = new Animation();
	up->AddFrame(2, 15, 16, 10, 160, 256);
	up->AddFrame(3, 15, 16, 10, 160, 256);

	down = new Animation();
	down->AddFrame(6, 15, 16, 10, 160, 256);
	down->AddFrame(7, 15, 16, 10, 160, 256);

	right = new Animation();
	right->AddFrame(0, 15, 16, 10, 160, 256);
	right->AddFrame(1, 15, 16, 10, 160, 256);

	left = new Animation();
	left->AddFrame(4, 15, 16, 10, 160, 256);
	left->AddFrame(5, 15, 16, 10, 160, 256);
}

void Game::Update()
{
	if (IsKeyPressed(KEY_W))
	{
		player->Translate(0, 5, 0);
		player->UpdateAnimation(up);
	}
	else if (IsKeyPressed(KEY_S))
	{
		player->Translate(0, -5, 0);
		player->UpdateAnimation(down);
	}
	else if (IsKeyPressed(KEY_A))
	{
		player->Translate(-5, 0, 0);
		player->UpdateAnimation(left);
	}
	else if (IsKeyPressed(KEY_D))
	{
		player->Translate(5, 0, 0);
		player->UpdateAnimation(right);
	}
	else
	{
		player->UpdateAnimation(idle);
	}

	player->Draw();
}

void Game::End()
{
	delete player;
}