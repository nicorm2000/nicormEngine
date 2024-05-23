#include "Window.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(float width, float height)
{
	this->window = nullptr;
	this->height = height;
	this->width = width;
}

Window::~Window()
{
}

int Window::InitLibrary()
{
	// Initialize the library
	if (!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

int Window::CreateWindow()
{
	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

	if (!window)
	{
		TerminateLibrary();
		return -1;
	}
}

void Window::MakeWindowContextCurrent()
{
	// Make the window's context current
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

bool Window::WindowShouldClose()
{
	// Check the user closes the window
	return glfwWindowShouldClose(window);
}

void Window::PollEvents()
{
	// Poll for and process events
	glfwPollEvents();
}

void Window::TerminateLibrary()
{
	// Finish the process of running the library
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLFWwindow* Window::GetWindow()
{
	return window;
}

float Window::GetHeight()
{
	return height;
}

float Window::GetWidth()
{
	return width;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}