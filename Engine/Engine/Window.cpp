#include "Window.h"
#include "Render.h"

Renderer* renderer = new Renderer();

int Window::WindowChecker()
{
    if (!glfwWindow)
    {
        CloseWindow();

        return -1;
    }
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

    while (!glfwWindowShouldClose(glfwWindow))
    {
        renderer->ClearScreen();

        renderer->PostRender(glfwWindow);
    }

    CloseWindow();

    delete renderer;

    return 0;
}