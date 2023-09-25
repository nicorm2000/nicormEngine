#include <iostream>
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
	Shape* shape = nullptr;

	void Start()
	{
		shape = new Shape(renderer);
		shape->CreateTriangle();
		shape->SetScale(100.0, 500.4, 500.6);
	}

	void Update()
	{
		shape->SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
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