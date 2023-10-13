#include "Game.h"

Game::Game()
{
	player = nullptr;
}

Game::~Game()
{
	if (player != nullptr) {
		player = nullptr;
		delete player;
	}
}

void Game::Start()
{
	player = new Sprite(renderer, "res/player.jpg");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(0, 0, 0);
	player->SetScale(100, 100, 100);
}

void Game::Update()
{
	if (IsKeyPressed(KEY_W))
	{
		player->Translate(0, 5, 0);
	}
	if (IsKeyPressed(KEY_D))
	{
		player->Translate(5, 0, 0);
	}
	if (IsKeyPressed(KEY_S))
	{
		player->Translate(0, -5, 0);
	}
	if (IsKeyPressed(KEY_A))
	{
		player->Translate(-5, 0, 0);
	}

	player->Draw();
}

void Game::End()
{
	delete player;
}