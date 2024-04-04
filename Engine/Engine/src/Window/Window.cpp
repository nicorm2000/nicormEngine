#include "Window.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(int newWidth, int newHeight)
{
    this->window = nullptr;
    this->width = newWidth;
    this->height = newHeight;
}

Window::~Window()
{
    if (window != nullptr)
    {
        window = nullptr;
        delete window;
    }
}

int Window::InitLibrary()
{
    //Initialize library
    if (!glfwInit()) return -1;

    //Specify the major version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //Specify the minor version of OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Specify whether the OpenGL context should be forward-compatible, will only support features from the specified version and earlier versions
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int Window::CreateWindow()
{
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (!window)
    {
        TerminateLibrary();

        return -1;
    }
    return 0;
}

void Window::MakeCurrentContext()
{
    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

bool Window::WindowShouldClose()
{
    return glfwWindowShouldClose(window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::TerminateLibrary()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::GetWindow()
{
    return window;
}

int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}