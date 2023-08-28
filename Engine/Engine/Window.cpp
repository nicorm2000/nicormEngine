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

    float positions[6] = {
        -0.5f, -0.5f,
         0.5f, 0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(glfwWindow))
    {
        render->ClearScreen();

        glDrawArrays(GL_TRIANGLES, 0, 3);

        render->PostRender(glfwWindow);
    }

    CloseWindow();

    delete render;

    return 0;
}