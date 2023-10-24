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

	player = new Sprite(renderer, "res/SpriteSheet3.png");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(400, 200, 0);
	player->SetScale(100, 100, 100);

	idle = new Animation();
	idle->AddFrame(4, 3, 4, 4, 2048, 2048);	

	up = new Animation();
	up->AddFrame(1, 4, 4, 4, 2048, 2048);
	up->AddFrame(2, 4, 4, 4, 2048, 2048);
	up->AddFrame(3, 4, 4, 4, 2048, 2048);
	up->AddFrame(4, 4, 4, 4, 2048, 2048);

	down = new Animation();
	down->AddFrame(1, 3, 4, 4, 2048, 2048);
	down->AddFrame(2, 3, 4, 4, 2048, 2048);
	down->AddFrame(3, 3, 4, 4, 2048, 2048);
	down->AddFrame(4, 3, 4, 4, 2048, 2048);

	right = new Animation();
	right->AddFrame(1, 1, 4, 4, 2048, 2048);
	right->AddFrame(2, 1, 4, 4, 2048, 2048);
	right->AddFrame(3, 1, 4, 4, 2048, 2048);
	right->AddFrame(4, 1, 4, 4, 2048, 2048);

	left = new Animation();
	left->AddFrame(1, 2, 4, 4, 2048, 2048);
	left->AddFrame(2, 2, 4, 4, 2048, 2048);
	left->AddFrame(3, 2, 4, 4, 2048, 2048);
	left->AddFrame(4, 2, 4, 4, 2048, 2048);

	player->SetCollider(true);
	tallGrass->SetCollider(true);
}

void Game::Update()
{
	glm::vec3 lastPosition = player->GetPosition();
	std::cout << lastPosition.x << ", " << lastPosition.y << std::endl;

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

	if (CollisionManager::CheckCollision(player, tallGrass))
	{
		player->SetPosition(lastPosition.x, lastPosition.y, lastPosition.z);
	}

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