#include "Game.h"
#include "Timer/Timer.h"

Game::Game()
{
	player = nullptr;
	sign = nullptr;
	grass = nullptr;
	signIdle = nullptr;
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

	if (sign != nullptr) {
		sign = nullptr;
		delete sign;
	}

	if (grass != nullptr) {
		grass = nullptr;
		delete grass;
	}

	if (signIdle != nullptr) {
		signIdle = nullptr;
		delete signIdle;
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
	renderer->SetDepth();

	grass = new Sprite(renderer, "res/bg.png");
	grass->SetColor(glm::vec3(1, 1, 1));
	grass->SetPosition(400, 400, 0);
	grass->SetScale(800, 800, 100);

	sign = new Sprite(renderer, "res/Sonic_Mania_Sprite_Sheet.png");
	sign->SetColor(glm::vec3(1, 1, 1));
	sign->SetPosition(550, 550, 0);
	sign->SetScale(100, 100, 100);

	player = new Sprite(renderer, "res/Sonic_Mania_Sprite_Sheet.png");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(400, 200, 0);
	player->SetScale(100, 100, 100);

	signIdle = new Animation();
	idle = new Animation();
	up = new Animation();
	down = new Animation();
	right = new Animation();
	left = new Animation();

	signIdle->AddFrame(133, 150, 49.5, 100, 832, 830, 1000, 4);

	idle->AddFrame(390, 98, 98 / 3, 43, 830, 465, 500, 3);
	up->AddFrame(18, 203, 122 / 3, 33, 830, 465, 500, 3);
	down->AddFrame(18, 203, 122 / 3, 33, 830, 465, 500, 3);
	right->AddFrame(18, 203, 122 / 3, 33, 830, 465, 500, 3);
	left->AddFrame(18, 203, 122 / 3, 33, 830, 465, 500, 3);
	//up->AddFrame(282, 401, 181 / 6, 29, 830, 465, 500, 6);
	//down->AddFrame(22, 354, 126 / 4, 40, 830, 465, 500, 4);
	//right->AddFrame(155, 199, 124 / 3, 43, 830, 465, 500, 3);
	//left->AddFrame(379, 152, 159 / 4, 43, 830, 465, 500, 4);

	player->SetAnimation(up);
	sign->SetAnimation(signIdle);

	player->SetCollider(true);
	sign->SetCollider(true);
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

	if (CollisionManager::CheckCollision(player, sign))
	{
		player->SetPosition(lastPosition.x, lastPosition.y, lastPosition.z);
	}

	player->UpdateAnimation();
	sign->UpdateAnimation();

	grass->Draw();
	sign->Draw();
	player->Draw();
}

void Game::End()
{
	delete signIdle;
	delete idle;
	delete up;
	delete down;
	delete right;
	delete left;
	delete player;
	delete sign;
	delete grass;
}