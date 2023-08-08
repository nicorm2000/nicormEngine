#include <glfw3.h>
#include <cmath>

void drawCircle(float centerX, float centerY, float radius, int segments)
{
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(centerX, centerY);

    for (int i = 0; i <= segments; ++i)
    {
        float angle = 2.0f * 3.14f * (float)(i) / (float)(segments);
        float x = radius * std::cos(angle) + centerX;
        float y = radius * std::sin(angle) + centerY;
        glVertex2f(x, y);
    }

    glEnd();
}

void drawTriangle()
{
    glBegin(GL_TRIANGLES);

    glVertex2f(-0.1f, -0.4f);
    glVertex2f(0.6f, -0.4f);
    glVertex2f(0.0f, 0.6f);

    glEnd();
}

void drawSquare()
{
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
}

float squareX = 0.0f;
float moveSpeed = 0.01f;

void drawMoveSquare()
{
    glBegin(GL_QUADS);
    glVertex2f(-0.5f + squareX, -0.5f);
    glVertex2f(0.5f + squareX, -0.5f);
    glVertex2f(0.5f + squareX, 0.5f);
    glVertex2f(-0.5f + squareX, 0.5f);
    glEnd();
}

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int screenWidth = 800, screenHeight = 600;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        squareX += moveSpeed;
        if (squareX > 1.5f)
            squareX = -1.5f;

        //drawMoveSquare();

        // Dibujar el cuadrado en movimiento
        /*glLoadIdentity();
        drawSquare();*/

        // Dibujar el triángulo
        /*glLoadIdentity();
        drawTriangle();*/

        // Dibujar el círculo
        //glLoadIdentity();
        //glColor3f(1.0f, 0.0f, 0.0f);  // Color rojo
        //drawCircle(0.0f, 0.0f, 0.3f, 100);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}