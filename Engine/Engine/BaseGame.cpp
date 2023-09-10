#include "BaseGame.h"

BaseGame::BaseGame()
{
	renderer = nullptr;
	window = nullptr;
}

BaseGame::~BaseGame()
{
	if (window != nullptr)
	{
		window = nullptr;
		delete window;
	}

	if (renderer != nullptr)
	{
		renderer = nullptr;
		delete renderer;
	}
}

int BaseGame::Run()
{
	window = new Window(1080, 720);

	renderer = new Render(window);

	window->CreateWindow();



	return 0;
}
