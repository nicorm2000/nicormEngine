#include "Input2.h"
namespace MikkaiEngine
{
	#define _GLFW_STICK 3

	Window* Input2::_window = nullptr;
	Camera2* Input2::_mainCam = nullptr;
	std::list<int> Input2::_currentKeysDown = std::list<int>();
	char                keys[GLFW_KEY_LAST + 1];
	bool firstMouse = true;

	float lastX = 0;
	float lastY = 0;

	void Input2::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		//std::cout << "callback_mouse: X:" << xposIn << " Y: " << yposIn << std::endl;
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;
		_mainCam->ProcessMouseMovement(xoffset, yoffset);
	}

	void Input2::key_callback(GLFWwindow* window,int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			_currentKeysDown.push_front(key);
		}
		else if (action == GLFW_RELEASE)
		{
			_currentKeysDown.remove(key);
		}
	}

	void Input2::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		_mainCam->ProcessMouseScroll(static_cast<float>(yoffset));
	}

	Input2::Input2(Window* w, Camera2* c)
	{
		_window	 = w;
		_mainCam = c;
		glfwSetInputMode(_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		lastX = _window->GetWidth() / 2.0f;
		lastY = _window->GetHeight() / 2.0f;
		glfwSetKeyCallback(_window->GetWindow(), key_callback);
		glfwSetCursorPosCallback(_window->GetWindow(), mouse_callback);
		glfwSetScrollCallback(_window->GetWindow(), scroll_callback);
	}
	void Input2::Init(Window* w, Camera2* c)
	{
		_window = w;
		_mainCam = c;
		glfwSetInputMode(_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		lastX = _window->GetWidth() / 2.0f;
		lastY = _window->GetHeight() / 2.0f;
		glfwSetKeyCallback(_window->GetWindow(), key_callback);
		glfwSetCursorPosCallback(_window->GetWindow(), mouse_callback);
		glfwSetScrollCallback(_window->GetWindow(), scroll_callback);
	}

	void Input2::mouse_callback(double xposIn, double yposIn)
	{
		//std::cout << "callback_mouse: X:" << xposIn << " Y: " << yposIn << std::endl;
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;
		_mainCam->ProcessMouseMovement(xoffset, yoffset);
	}



	bool Input2::IsKeyDown(KeyCode keyCode) {
		std::list<int>::iterator it = find(_currentKeysDown.begin(), _currentKeysDown.end(), keyCode);
		if (it != _currentKeysDown.end())
		{
			_currentKeysDown.remove(keyCode);
			return true;
		}
		return false;
	}
	bool Input2::IsKeyPressed(KeyCode keyCode) {
		int aux = glfwGetKey(_window->GetWindow(), keyCode);
		return aux == GLFW_PRESS;
	}
	bool Input2::IsKeyUp(KeyCode keyCode) {
		int aux = glfwGetKey(_window->GetWindow(), keyCode);
		return aux == GLFW_RELEASE;



	}
	void Input2::lock_cursor(bool value)
	{
		if (value)
			glfwSetInputMode(Input2::_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(Input2::_window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	int Input2::GetKey(int key)
	{
		GLFWwindow* window = _window->GetWindow();
		int mod = glfwGetKey(window, key);
		assert(window != NULL);
		if (!window)
			return KEY_UNKNOWN;

		if (key < GLFW_KEY_SPACE || key > GLFW_KEY_LAST)
		{
			std::cout << GLFW_INVALID_ENUM << " Invalid key %i : " << key << std::endl;
			return KEY_UNKNOWN;
		}

		if (keys[key] == _GLFW_STICK)
		{
			// Sticky mode: release key now
			keys[key] = GLFW_RELEASE;
			return GLFW_PRESS;
		}

		if (keys[key] == GLFW_PRESS)
		{
			keys[key] = 1;
		}
		return (int)keys[key];
	}
}