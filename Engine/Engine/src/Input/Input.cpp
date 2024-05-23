#include "Input.h"

Window* Input::window = nullptr;
Camera* Input::camera = nullptr;
Render* Input::renderer = nullptr;

list<int> Input::keysDown = std::list<int>();
glm::vec2 Input::lastPosition = glm::vec2(0.0f);
bool Input::firstMouse = true;

Input::Input()
{

}

Input::~Input()
{

}

void Input::Init(Window* wind, Camera* cam, Render* render)
{
	window = wind;
	renderer = render;
	//SetCamera(cam);

	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
	glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetScrollCallback(window->GetWindow(), ScrollCallback);
}

void Input::SetCamera(Camera* cam)
{
	camera = cam;
}

bool Input::IsKeyPressed(int keycode)
{
	int aux = glfwGetKey(window->GetWindow(), keycode);
	return aux == GLFW_PRESS;
}

bool Input::IsKeyDown(int keycode)
{
	list<int>::iterator it = find(keysDown.begin(), keysDown.end(), keycode);

	if (it != keysDown.end())
	{
		keysDown.remove(keycode);
		return true;
	}

	return false;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) keysDown.push_front(key);
	else if (action == GLFW_RELEASE) keysDown.remove(key);
}

void Input::MouseCallback(GLFWwindow* window, double posX, double posY)
{
	if (firstMouse)
	{
		lastPosition.x = posX;
		lastPosition.y = posY;
		firstMouse = false;
	}

	glm::vec2 offsetPosition;
	offsetPosition.x = posX - lastPosition.x;
	offsetPosition.y = lastPosition.y - posY;

	lastPosition.x = posX;
	lastPosition.y = posY;

	float sensitivity = 0.1f;

	offsetPosition.x *= renderer->GetSensitivity() * sensitivity;
	offsetPosition.y *= renderer->GetSensitivity() * sensitivity;
	//offsetPosition.x *= camera->GetSensitivity();
	//offsetPosition.y *= camera->GetSensitivity();
	
	renderer->SetYaw(renderer->GetYaw() + offsetPosition.x);
	renderer->SetPitch(renderer->GetPitch() + offsetPosition.y);
	//camera->SetYaw(camera->GetYaw() + offsetPosition.x);
	//camera->SetPitch(camera->GetPitch() + offsetPosition.y);

	//camera->Rotate();
	if (renderer->GetPitch() > 89.0f)renderer->SetPitch(89.0f);
	if (renderer->GetPitch() < -89.0f)renderer->SetPitch(-89.0f);

	renderer->UpdateDirection();
}

void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	renderer->SetFOV(renderer->GetFOV() - (float)yoffset);

	if (renderer->GetFOV() < 1.0f)
		renderer->SetFOV(1.0f);
	if (renderer->GetFOV() > 120.0f)
		renderer->SetFOV(120.0f);
	//camera->SetFOV(camera->GetFOV() - (float)yoffset);
	//
	//if (camera->GetFOV() < 1.0f) camera->SetFOV(1.0f);
	//if (camera->GetFOV() > 45.0f) camera->SetFOV(45.0f);
}