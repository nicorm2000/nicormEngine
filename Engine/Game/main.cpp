#include <iostream>
#include "BaseGame/BaseGame.h"

class Game : public BaseGame
{
	Shape* shape = nullptr;

	void Start()
	{
		shape = new Shape(renderer);
		shape->CreateTriangle();
		shape->SetPosition(400, 300, 0);
		shape->SetScale(10, 10, 1);
		std::cout << std::to_string(shape->GetPosition().x);
		std::cout << std::to_string(shape->GetPosition().y);
		std::cout << std::to_string(shape->GetPosition().z);

		renderer->ClearScreenWithColor(1, 0, 0, 1);
	}

	void Update()
	{
		//shape->SetRotation(0.1, 0.0, 0.0);
		//shape->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
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