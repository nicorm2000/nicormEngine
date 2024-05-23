#ifndef INPUT_H
#define INPUT_H

#include <glew.h>
#include <glfw3.h>
#include "Window/Window.h"
#include "Camera/Camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "Keycodes.h"
#include <list>
using namespace std;

class DllApi Input
{
private:
	static Window* window;
	static Camera* camera;

	static list<int> keysDown;
	static glm::vec2 lastPosition;
	static bool firstMouse;

public:
	Input();
	~Input();

	static void Init(Window* wind, Camera* cam);
	static void SetCamera(Camera* cam);
	static bool IsKeyPressed(int keycode);
	static bool IsKeyDown(int keycode);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double posX, double posY);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif