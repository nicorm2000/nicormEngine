#include "Window.h"
#include "Render.h"

Render* render = new Render();

int Window::WindowChecker()
{
    if (!glfwWindow)
    {
        CloseWindow();

        return -1;
    }

    return 0;
}

void Window::CloseWindow()
{
    glfwTerminate();
}

void Window::MakeCurrentContext(GLFWwindow* glfwWindow)
{
    glfwMakeContextCurrent(glfwWindow);
}

int Window::InitWindow()
{
    glfwWindow = glfwCreateWindow(width, height, title, NULL, glfwWindow);

    WindowChecker();

    MakeCurrentContext(glfwWindow);

    //unsigned int buffer;
    //glGenBuffers(1, &buffer);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        render->ClearScreen();

        render->DrawTriangle(0, 0, 0);

        render->PostRender(glfwWindow);
    }

    CloseWindow();

    delete render;

    return 0;
}