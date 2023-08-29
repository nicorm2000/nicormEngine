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

    if (glewInit() != GLEW_OK) {
        return -1;
    }

    while (!glfwWindowShouldClose(glfwWindow))
    {
        render->ClearScreen();

        render->DrawTriangle(0.0f, 0.0f);

        render->PostRender(glfwWindow);
    }

    CloseWindow();

    delete render;

    return 0;
}