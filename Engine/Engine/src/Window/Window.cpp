#include "Window.h"

Window::Window(int width, int height)
{
    glfwWindow = nullptr;
    this->width = width;
    this->height = height;
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
}

void Window::CloseWindow()
{
    glfwTerminate();
}

void Window::MakeCurrentContext()
{
    glfwMakeContextCurrent(glfwWindow);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(glfwWindow);
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