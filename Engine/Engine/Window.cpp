#include "Window.h"

Window::Window(int width, int height)
{
    glfwWindow = nullptr;
    width = this->width;
    height = this->height;
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

void Window::MakeCurrentContext(GLFWwindow* glfwWindow)
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

//int Window::InitWindow()
//{
//    CreateWindow();
//
//    MakeCurrentContext(glfwWindow);
//
//    if (glewInit() != GLEW_OK) {
//        return -1;
//    }
//
//    while (!glfwWindowShouldClose(glfwWindow))
//    {
//        render->ClearScreen();
//
//        render->DrawTriangle(0.0f, 0.0f);
//
//        render->PostRender(glfwWindow);
//    }
//
//    CloseWindow();
//
//    delete render;
//
//    return 0;
//}

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