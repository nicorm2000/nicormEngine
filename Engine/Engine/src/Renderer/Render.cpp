#include "Render.h"
#include <fstream>
#include <iostream>
#include <sstream>

Render::Render(Window* window)
{
    window = this->window;
}

Render::~Render()
{
    if (window != nullptr)
    {
        window = nullptr;
        delete window;
    }
}

void Render::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
    glClearColor(r, g, b, a);
    ClearScreen();
}

void Render::SwapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}

int Render::InitGLEW()
{
    if (glewInit() != GLEW_OK) return -1;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::InitMaterial()
{
    material = new Material();
    ShaderProgramSource source = material->ParseShader("Basic.shader");
    material->CreateMaterial(source.VertexSource, source.FragmentSource);
    material->UseMaterial();
}

void Render::CreateBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void Render::BindBuffers(GLsizeiptr sizeVertices, GLsizeiptr sizeIndices, const GLvoid* vertices, const GLvoid* indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glBindVertexArray(VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeVertices, vertices, GL_STATIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);
}

void Render::UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Render::EnableVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset)
{
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}

void Render::DrawWithoutIndexBuffer(GLenum primitive, GLint offset, GLsizei count)
{
    glDrawArrays(primitive, offset, count);
}

void Render::DrawWithIndexBuffer(GLenum primitive, GLsizei count, GLenum type, const GLvoid* indices, unsigned int& VAO)
{
    glBindVertexArray(VAO);

    glDrawElements(primitive, count, type, indices);
    glBindVertexArray(0);
}

Material* Render::GetMaterial()
{
    return material;
}