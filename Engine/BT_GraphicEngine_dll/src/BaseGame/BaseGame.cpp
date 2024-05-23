#include "BaseGame.h"

BaseGame::BaseGame()
{
	window = nullptr;
	renderer = nullptr;
	camera = nullptr;
}

BaseGame::~BaseGame()
{
	if (window != nullptr)
	{
		delete window;
		window = nullptr;
	}

	if (renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}

	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}
}

void BaseGame::Run()
{
	window->InitLibrary();

	window = new Window(1080, 720);

	window->CreateWindow();
	window->MakeWindowContextCurrent();

	renderer->InitGLEW();

	renderer = new Renderer();

	renderer->InitShader();

	camera = new Camera(renderer);
	camera->Init(45.f, window->GetWidth(), window->GetHeight(), 0.1f, 100.f);
	camera->SetSensitivity(0.25f);

	Input::Init(window, camera);
	OcclusionCulling::Init(camera);
	MaterialManager::Init(renderer);

	BSP::Init(renderer, camera);

	srand(time(NULL));

	Begin();

	while (!window->WindowShouldClose())
	{
		renderer->ClearScreen();

		Timer::Update(glfwGetTime());
		camera->Update();
		OcclusionCulling::Update();

		Update();
		BSP::Update();
		Draw();
		
		renderer->SwapBuffers(window);
		window->PollEvents();
	}

	End();
	BSP::DeInit();
	MaterialManager::DeInit();
	window->TerminateLibrary();
	glfwTerminate();
}