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

void Render::DrawTriangle(float x, float y)
{
    float positions[6] = {
        -0.5f + x, -0.5f + y,
         0.5f + x, 0.5f + y,
         0.5f + x, -0.5f + y
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}