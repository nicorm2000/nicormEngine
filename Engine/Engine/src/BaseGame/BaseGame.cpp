#include "BaseGame.h"
#include "Timer/Timer.h"

BaseGame::BaseGame()
{
	renderer = nullptr;
	window = nullptr;
	input = nullptr;
	collisionManager = nullptr;
	camera = nullptr;
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

	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
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

	///camera = new Camera(renderer);
	//camera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
	//camera->SetSensitivity(0.25f);

	Input::Init(window, camera, renderer);

	srand(time(NULL));

	Start();

	while (!window->WindowShouldClose())
	{
		Timer::Update(glfwGetTime());

		renderer->ClearScreen();

		//camera->Update();

		Update();

		renderer->SwapBuffers(window->GetWindow());

		window->PollEvents();
	}

	End();

	window->TerminateLibrary();

	return 0;
}

bool BaseGame::IsKeyPressed(int keycode)
{
	return input->IsKeyPressed(keycode);
}

float BaseGame::GetFrameTime()
{
	return glfwGetTime();
}