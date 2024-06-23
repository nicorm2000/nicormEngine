#include "BaseGame.h"

BaseGame::BaseGame() {
	_input = nullptr;
	_mainCamera = nullptr;
	_mainCamera2 = nullptr;
	_renderer = nullptr;
	_time = nullptr;
	_window = nullptr;
	//_input2 = nullptr;
	//backgroundColor = glm::vec4();

}
BaseGame::~BaseGame() {
	if (_window != nullptr) {
		_window = nullptr;
		delete _window;
	}
	if (_renderer != nullptr) {
		_renderer = nullptr;
		delete _renderer;
	}
}

int BaseGame::MainLoop(int width, int height, const char* windowName)
{
	if (InitEngine(width, height, windowName))
	{
		Init();
		while (!glfwWindowShouldClose(_window->GetWindow())) {
			
			_renderer->ClearScreen();
			_time->Update();
			if (imGuiEnabled)
			{
				_myImgui->Update();
				UpdateImgui();
			}
			Update();
			if (imGuiEnabled)
			_myImgui->Draw();
			Draw();
			_renderer->PostRender(GetWindow());
		}
	}
	Deinit();
	DeinitEngine();
	return 0;
}
void BaseGame::DeinitEngine()
{
	glfwTerminate();
}
Window* BaseGame::GetWindow() {
	return _window;
}
bool BaseGame::InitEngine(int windowSizeX, int windowSizeY, std::string windowName)
{
	std::cout << "+Init Engine" << std::endl;
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return false;
	if (!InitWindow(windowSizeX,windowSizeY,windowName))
		return false;
	if (!InitGlew())
		return false;
	InitRender();
	InitTime();
	InitCamera();
	InitInput();
	MikkaiEngine::MaterialManager::Init(_renderer);
	if (imGuiEnabled)
	InitImgur();
	std::cout << "-Init Engine" << std::endl;
	return true;
}
Renderer* BaseGame::GetRenderer() {
	return _renderer;
}

double BaseGame::getCurrentTime()
{
	return glfwGetTime();
}
bool BaseGame::IsKeyDown(Input::KeyCode key) { return Input::IsKeyDown(key); }
bool BaseGame::IsKeyRelease(Input::KeyCode key) { return Input::IsKeyPressed(key); }
bool BaseGame::IsKeyUp(Input::KeyCode key) { return Input::IsKeyUp(key); }

bool BaseGame::InitGlew() {
	if (glewInit() != GLEW_OK) // tiene que ir despues de la creacion del contexto de glfw si o si
	{
		std::cout << "Glew error" << std::endl;
		return false;
	}
	return true;
}

void BaseGame::InitImgur()
{
	_myImgui = new MyImGui();
	_myImgui->Init();
	_myImgui->InitAfterWindow(_window);
}
void BaseGame::InitInput() {
	Input::SetWindow(_window);
	Input::StartInputSystem();
	Input::SetCam(_mainCamera2);
}
void BaseGame::InitCamera() {
	_mainCamera = new Camera();
	_mainCamera->Init(_renderer,_window);
	_mainCamera2 = new MikkaiEngine::Camera2(_renderer,_window);
}

bool BaseGame::InitWindow(int windowSizeX, int windowSizeY, std::string windowName) {
	_window = new Window(windowSizeX, windowSizeY, windowName);
	if (!_window->GetWindow())
	{
		glfwTerminate();
		delete _window;
		return false;
	}
	_window->Start();
	return true;
}

void BaseGame::InitRender() {
	_renderer = new Renderer();
	_renderer->Init();
}
void BaseGame::InitTime() {
	_time = new Time();
}


void BaseGame::SetBackGroundColor(color::RGBA color) {
	_renderer->SetBackgroundColor(color.GetColorV4());
}