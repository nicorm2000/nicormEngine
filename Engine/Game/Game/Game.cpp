#include "Game.h"
#include "Timer/Timer.h"

Game::Game()
{
	player = nullptr;
	player2 = nullptr;
	tallGrass = nullptr;
	grass = nullptr;
	idle = nullptr;
	up = nullptr;
	down = nullptr;
	left = nullptr;
	right = nullptr;
	idle2 = nullptr;
	up2 = nullptr;
	down2 = nullptr;
	left2 = nullptr;
	right2 = nullptr;
	time = 0;
}

Game::~Game()
{
	if (player != nullptr) {
		player = nullptr;
		delete player;
	}

	if (player2 != nullptr) {
		player2 = nullptr;
		delete player2;
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

	if (idle2 != nullptr) {
		idle2 = nullptr;
		delete idle2;
	}

	if (up2 != nullptr) {
		up2 = nullptr;
		delete up2;
	}

	if (down2 != nullptr) {
		down2 = nullptr;
		delete down2;
	}

	if (left2 != nullptr) {
		left2 = nullptr;
		delete left2;
	}

	if (right2 != nullptr) {
		right2 = nullptr;
		delete right2;
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

	player2 = new Sprite(renderer, "res/SpriteSheet4.png");
	player2->SetColor(glm::vec3(1, 1, 1));
	player2->SetPosition(400, 600, 0);
	player2->SetScale(100, 100, 100);

	idle = new Animation();
	up = new Animation();
	down = new Animation();
	right = new Animation();
	left = new Animation();

	idle->AddFrame(0, 3, 4, 4, 2048, 2048);

	for (int i = 1; i < 5; i++)
	{
		up->AddFrame(i, 0, 4, 4, 2048, 2048);
		down->AddFrame(i, 3, 4, 4, 2048, 2048);
		right->AddFrame(i, 1, 4, 4, 2048, 2048);
		left->AddFrame(i, 2, 4, 4, 2048, 2048);
	}

	idle2 = new Animation();
	up2 = new Animation();
	down2 = new Animation();
	right2 = new Animation();
	left2 = new Animation();

	idle2->AddFrame(0, 3, 4, 4, 2048, 2048);

	for (int i = 1; i < 5; i++)
	{
		up2->AddFrame(i, 0, 4, 4, 2048, 2048);
		down2->AddFrame(i, 3, 4, 4, 2048, 2048);
		right2->AddFrame(i, 1, 4, 4, 2048, 2048);
		left2->AddFrame(i, 2, 4, 4, 2048, 2048);
	}

	player->SetCollider(true);
	player2->SetCollider(true);
	tallGrass->SetCollider(true);
}

void Game::Update()
{
	glm::vec3 lastPosition = player->GetPosition();
	glm::vec3 lastPosition2 = player2->GetPosition();

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

	if (IsKeyPressed(KEY_UP))
	{
		player2->Translate(0, 5, 0);
		player2->UpdateAnimation(up2);
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		player2->Translate(0, -5, 0);
		player2->UpdateAnimation(down2);
	}
	else if (IsKeyPressed(KEY_LEFT))
	{
		player2->Translate(-5, 0, 0);
		player2->UpdateAnimation(left2);
	}
	else if (IsKeyPressed(KEY_RIGHT))
	{
		player2->Translate(5, 0, 0);
		player2->UpdateAnimation(right2);
	}
	else
	{
		player2->UpdateAnimation(idle2);
	}

	if (CollisionManager::CheckCollision(player, tallGrass))
	{
		player->SetPosition(lastPosition.x, lastPosition.y, lastPosition.z);
	}

	if (CollisionManager::CheckCollision(player2, tallGrass))
	{
		player2->SetPosition(lastPosition2.x, lastPosition2.y, lastPosition2.z);
	}

	grass->Draw();
	tallGrass->Draw();
	player->Draw();
	player2->Draw();
}

void Game::End()
{
	delete player;
	delete player2;
	delete tallGrass;
	delete grass;
}