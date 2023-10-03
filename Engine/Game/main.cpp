#include <iostream>
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
	Shape* shape = nullptr;
	glm::vec3 red = { 1, 0, 0 };

	void Start()
	{
		shape = new Shape(renderer);
		shape->CreateTriangle();
		shape->SetColor(red);
		shape->SetScale(100, 100, 1);
		shape->SetPosition(0, 0, 0);
	}

	void Update()
	{
		shape->Draw();
	}

	void End()
	{
		delete shape;
	}
};

int main()
{
	Game* game = new Game();

	game->Run();

	delete game;
	return 0;
}