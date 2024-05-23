#include "Game.h"
#include "Timer/Timer.h"

Game::Game()
{
	player = nullptr;
	sign = nullptr;
	bg = nullptr;
	signIdle = nullptr;
	idle = nullptr;
	up = nullptr;
	down = nullptr;
	left = nullptr;
	right = nullptr;
	time = 0;
	cameraSpeed = 0.25f;
	cameraSpeedMultiplier = 5.0f;
	deltaTime = 0.0f;
	lastFrame = 0.0f;
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);

	firstPerson = true;
	thirdPerson = false;
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

	if (bg != nullptr) {
		bg = nullptr;
		delete bg;
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

	bg = new Sprite(renderer, "res/bg.png");
	bg->SetColor(glm::vec3(1, 1, 1));
	bg->SetPosition(0, -2, 0);
	bg->SetScale(20, 20, 1);
	bg->SetRotationX(90);
	bg->SetRotationZ(180);

	sign = new Sprite(renderer, "res/Sonic_Mania_Sprite_Sheet.png");
	sign->SetColor(glm::vec3(1, 1, 1));
	sign->SetPosition(0, 0, -9);
	sign->SetScale(5, 5, 1);

	player = new Sprite(renderer, "res/Sonic_Mania_Sprite_Sheet.png");
	player->SetColor(glm::vec3(1, 1, 1));
	player->SetPosition(0, 0, -8);
	player->SetScale(3, 3, 1);

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
}

void Game::Update()
{
	if (IsKeyPressed(KEY_P))
	{
		firstPerson = !firstPerson;
		thirdPerson = !thirdPerson;
	}

	float currentFrame = GetFrameTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	cameraSpeed = cameraSpeedMultiplier * deltaTime;

	glm::vec3 lastPosition = player->GetPosition();

	if (IsKeyPressed(KEY_0))
	{
		player->Translate(0, 0.1, 0);
		player->SetAnimation(up);
	}
	else if (IsKeyPressed(KEY_1))
	{
		player->Translate(0, -0.1, 0);
		player->SetAnimation(down);
	}
	else if (IsKeyPressed(KEY_2))
	{
		player->Translate(-0.1, 0, 0);
		player->SetAnimation(left);
	}
	else if (IsKeyPressed(KEY_3))
	{
		player->Translate(0.1, 0, 0);
		player->SetAnimation(right);
	}
	else
	{
		player->SetAnimation(idle);
	}

	if (firstPerson && !thirdPerson)
	{
		if (IsKeyPressed(KEY_W))
		{
			renderer->UpdateCameraPos(cameraPos += cameraSpeed * renderer->GetFront());
		}
		else if (IsKeyPressed(KEY_S))
		{
			renderer->UpdateCameraPos(cameraPos -= cameraSpeed * renderer->GetFront());
		}
		else if (IsKeyPressed(KEY_A))
		{
			renderer->UpdateCameraPos(cameraPos -= glm::normalize(glm::cross(renderer->GetFront(), renderer->GetUp())) * cameraSpeed);
		}
		else if (IsKeyPressed(KEY_D))
		{
			renderer->UpdateCameraPos(cameraPos += glm::normalize(glm::cross(renderer->GetFront(), renderer->GetUp())) * cameraSpeed);
		}
	}
	///if (!firstPerson && thirdPerson)
	///{
	///	if (IsKeyPressed(KEY_U))
	///	{
	///		renderer->UpdateCameraPos(cameraPos += cameraSpeed);
	///	}
	///	else if (IsKeyPressed(KEY_J))
	///	{
	///		renderer->UpdateCameraPos(cameraPos -= cameraSpeed);
	///	}
	///	else if (IsKeyPressed(KEY_H))
	///	{
	///		renderer->UpdateCameraPos(cameraPos -= glm::normalize(glm::cross(renderer->GetFront(), renderer->GetUp())) * cameraSpeed);
	///	}
	///	else if (IsKeyPressed(KEY_K))
	///	{
	///		renderer->UpdateCameraPos(cameraPos += glm::normalize(glm::cross(renderer->GetFront(), renderer->GetUp())) * cameraSpeed);
	///	}
	///}

	//if (CollisionManager::CheckCollision(player, sign))
	//{
	//	player->SetPosition(lastPosition.x, lastPosition.y, lastPosition.z);
	//}

	player->UpdateAnimation();
	sign->UpdateAnimation();

	bg->Draw();
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
	delete bg;
}