#include <iostream>
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
	Shape* shape;

	void Start() override
	{
		shape = new Shape(renderer);
		shape->CreateTriangle();
	}

	void Update() override
	{
		shape->Draw();
		shape->Rotate(90.0f, 0.0f, 0.0f);
	}

	void End() override
	{
		delete shape;
	}
};

int main()
{
	Game* game = new Game();

	game->Run();

	delete game;

	system("pause");
	return 0;
}