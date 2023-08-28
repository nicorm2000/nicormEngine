#include "Render.h"

void Render::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Render::PostRender(GLFWwindow* window)
{
	glfwSwapBuffers(window);

	glfwPollEvents();
}

void Render::DrawTriangle(float x, float y, float z)
{
	
}