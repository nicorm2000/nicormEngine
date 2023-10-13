#ifndef INPUT_H
#define INPUT_H

#include <list>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Window/window.h"
#include "Export.h"
#include "Keycodes.h"

class Window;

class DllApi Input
{
private:

public:
	Input(Window* window);
	~Input();

	static bool IsKeyPressed(int keycode, Window* window);
};

#endif