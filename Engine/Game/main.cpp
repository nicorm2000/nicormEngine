#include <iostream>
#include "BaseGame.h"

class Game : public BaseGame
{
	void Start() override
	{

	}

	void Update() override
	{

	}

	void End() override
	{

	}
};

int main()
{
	Game* game = new Game();

	game->Run();

	system("pause");
	return 0;
}