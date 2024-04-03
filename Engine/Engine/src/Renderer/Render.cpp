#include "Render.h"
#include <fstream>
#include <iostream>
#include <sstream>

Render::Render(Window* window)
{
    this->window = window;

    projection = glm::ortho(0.0f, (float)window->GetWidth(), 0.0f, (float)window->GetHeight(), 0.1f, 500.0f);
    view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

Render::~Render()
{
    if (window != nullptr)
    {
        window = nullptr;
        delete window;
    }
}

void Render::SetDepth()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
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
    //PUEDE TENER PROBLEMAS
    material = new Material();
    ShaderProgramSource source = material->ParseShader("shaders/Textures.shader");
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

void Render::BindTexture(GLenum target, GLuint texture)
{
    glBindTexture(target, texture);
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

glm::mat4 Render::GetViewMatrix()
{
    return view;
}

glm::mat4 Render::GetProjectionMatrix()
{
    return projection;
}

Material* Render::GetMaterial()
{
    return material;
}