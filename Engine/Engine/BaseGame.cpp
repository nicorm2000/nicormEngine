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

	window->InitLibrary();

	window->CreateWindow();

	window->MakeCurrentContext();

	renderer->InitGLEW();

	renderer->InitMaterial();

	Start();

	while (!window->WindowShouldClose())
	{
		renderer->ClearScreen();

		Update();

		renderer->SwapBuffers(window->GetWindow());

		window->PollEvents();
	}

	End();

	window->CloseWindow();

	return 0;
}