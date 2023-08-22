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
	float vertices[] = {
		-0.5f + x, -0.5f + y, 0.0f + z,
		 0.5f + x, -0.5f + y, 0.0f + z,
		 0.0f + x,  0.5f + y, 0.0f + z
	};

	glBegin(GL_TRIANGLES);
}