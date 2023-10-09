#include "Game.h"

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Start()
{
	shape = new Shape(renderer);
	shape->CreateTriangle();
	shape->SetColor(red);
	shape->SetScale(100, 100, 1);
	shape->SetPosition(0, 0, 0);
}

void Game::Update()
{
	shape->Draw();

	if (IsKeyPressed(KEY_W))
	{
		shape->SetPosition(0, 10, 0);
	}
	if (IsKeyPressed(KEY_D))
	{
		shape->SetPosition(10, 0, 0);
	}
	if (IsKeyPressed(KEY_S))
	{
		shape->SetPosition(0, -10, 0);
	}
	if (IsKeyPressed(KEY_A))
	{
		shape->SetPosition(-10, 0, 0);
	}
}

void Game::End()
{
	delete shape;
}