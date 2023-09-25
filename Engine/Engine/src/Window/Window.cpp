#include "Window.h"

Window::Window(int newWidth, int newHeight)
{
    glfwWindow = nullptr;
    width = newWidth;
    height = newHeight;
}

Window::~Window()
{
    if (glfwWindow != nullptr)
    {
        glfwWindow = nullptr;
        delete glfwWindow;
    }
}

int Window::InitLibrary()
{
    if (!glfwInit()) return -1;
}

int Window::CreateWindow()
{
    glfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!glfwWindow)
    {
        CloseWindow();

        return -1;
    }
    return 0;
}

void Window::MakeCurrentContext()
{
    glfwMakeContextCurrent(glfwWindow);
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::CloseWindow()
{
    glfwTerminate();
}

GLFWwindow* Window::GetWindow()
{
    return glfwWindow;
}

int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}