#include "Window.h"
#include "Export.h"

Window* window = new Window();

int main(void)
{
    if (!glfwInit())
        return -1;

    window->InitWindow();

    delete window;
}