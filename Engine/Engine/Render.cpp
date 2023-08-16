#include "Render.h"

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::PostRender(GLFWwindow* window)
{
	glfwSwapBuffers(window);

	glfwPollEvents();
}