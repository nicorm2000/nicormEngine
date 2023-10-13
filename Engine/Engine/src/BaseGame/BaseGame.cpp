#include "BaseGame.h"

BaseGame::BaseGame()
{
	renderer = nullptr;
	window = nullptr;
	input = nullptr;
	collisionManager = nullptr;
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

	if (input != nullptr) {
		input = nullptr;
		delete input;
	}

	if (collisionManager != nullptr) {
		collisionManager = nullptr;
		delete collisionManager;
	}
}

int BaseGame::Run()
{
	window = new Window(800, 800);

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

bool BaseGame::IsKeyPressed(int keycode)
{
	return input->IsKeyPressed(keycode, window);
}