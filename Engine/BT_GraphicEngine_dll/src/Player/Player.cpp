#include "Player.h"

Player::Player() : Entity3D()
{
	camera = nullptr;
	moveBaseSpeed = 0.f;
	moveSpeed = 0.f;
	rotSpeed = 0.f;
}

Player::Player(Renderer* renderer) : Entity3D(renderer)
{
	camera = nullptr;
	moveBaseSpeed = 0.f;
	moveSpeed = 0.f;
	rotSpeed = 0.f;
}

Player::~Player()
{
}

void Player::Init(Camera* camera, float moveSpeed, float rotSpeed)
{
	this->camera = camera;
	this->moveSpeed = moveSpeed;
	this->rotSpeed = rotSpeed;
	moveBaseSpeed = moveSpeed;
}

void Player::Update()
{
	Inputs();
}

void Player::Inputs()
{
	if (Input::IsKeyPressed(KEY_A) || Input::IsKeyPressed(KEY_LEFT))
	{
		SetPosition(GetPosition() - glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
	}
	else if (Input::IsKeyPressed(KEY_D) || Input::IsKeyPressed(KEY_RIGHT))
	{
		SetPosition(GetPosition() + glm::normalize(glm::cross(camera->GetForward(), camera->GetUp())) * GetSpeedDelta());
	}
	else if (Input::IsKeyPressed(KEY_W) || Input::IsKeyPressed(KEY_UP))
	{
		SetPosition(GetPosition() + GetSpeedDelta() * camera->GetForward());
	}
	else if (Input::IsKeyPressed(KEY_S) || Input::IsKeyPressed(KEY_DOWN))
	{
		SetPosition(GetPosition() - GetSpeedDelta() * camera->GetForward());

	}

	if (Input::IsKeyPressed(KEY_Q))
	{
		camera->SetFollowStatus(true);
	}
	else if (Input::IsKeyPressed(KEY_E))
	{
		camera->SetFollowStatus(false);
	}
	if (Input::IsKeyPressed(KEY_LEFT_SHIFT))
	{
		moveSpeed = moveBaseSpeed * 2.5f;
	}
	else
	{
		moveSpeed = moveBaseSpeed;
	}

	/*if (Input::IsKeyPressed(KEY_R))
	{
		SetPosition(glm::vec3(0.f));
	}*/
}

float Player::GetSpeedDelta()
{
	return moveSpeed * Timer::GetDeltaTime();
}