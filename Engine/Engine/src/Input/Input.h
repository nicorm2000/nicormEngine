#ifndef INPUT_H
#define INPUT_H

#include <list>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Window/window.h"
#include "Camera/Camera.h"
#include "Export.h"
#include "Keycodes.h"

using namespace std;

class Window;

class DllApi Input
{
private:
	static Window* window;
	static Camera* camera;
	static Render* renderer;

	static list<int> keysDown;
	static glm::vec2 lastPosition;
	static bool firstMouse;

public:
	Input(Window* window);
	//Input();
	~Input();


	static void Init(Window* wind, Camera* cam, Render* render);
	static void SetCamera(Camera* cam);
	//static bool IsKeyPressed(int keycode);
	static bool IsKeyPressed(int keycode, Window* window);
	static bool IsKeyDown(int keycode);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double posX, double posY);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif