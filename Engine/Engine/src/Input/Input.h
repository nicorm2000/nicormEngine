#ifndef INPUT_H
#define INPUT_H

#include <list>
#include "glm/glm.hpp"
#include "Window/window.h"
#include "Export.h"

class DllApi Input
{
private:
	static std::list<int> currentKeysDown;
	static glm::vec2 mousePosition;

public:
	Input(Window* window);
	~Input();

	static bool IsKeyPressed(int keycode, Window* window);
	static bool IsKeyDown(int keycode, Window* window);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif