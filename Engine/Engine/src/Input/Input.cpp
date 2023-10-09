#include "Input.h"

std::list<int> Input::currentKeysDown = std::list<int>();
glm::vec2 Input::mousePosition = glm::vec2(0.f);
bool Input::firstMouse = true;

Input::Input(Window* window)
{
	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Input::~Input()
{

}

bool Input::IsKeyPressed(int keycode, Window* window)
{
	int aux = glfwGetKey(window->GetWindow(), keycode);
	return aux == GLFW_PRESS;
}

bool Input::IsKeyDown(int keycode, Window* window)
{
	std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keycode);
	if (it != currentKeysDown.end())
	{
		currentKeysDown.remove(keycode);
		return true;
	}
	return false;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		currentKeysDown.push_front(key);
	}
	else if (action == GLFW_RELEASE)
	{
		currentKeysDown.remove(key);
	}
}