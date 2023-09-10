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


ShaderProgramSource Render::ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;

    std::stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }

    }

    return { ss[0].str(), ss[1].str() };
}

//void Render::PostRender(GLFWwindow* window)
//{
//	glfwSwapBuffers(window);
//
//	glfwPollEvents();
//}
//
//void Render::DrawTriangle(float x, float y)
//{
//    float positions[] = {
//        -0.5f + x, -0.5f + y,
//         0.5f + x, -0.5f + y,
//         0.5f + x, 0.5f + y,
//         -0.5f + x, 0.5f + y,
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//
//    unsigned int buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
//
//    unsigned int ibo;
//    glGenBuffers(1, &ibo);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 2 * sizeof(unsigned int), indices, GL_STATIC_DRAW);
//
//    ShaderProgramSource source = ParseShader("Basic.shader");
//
//    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
//    glUseProgram(shader);
//
//    //CUALQUIER INDEX BUFFER ESTA HECHO DE UNSIGNED INTS
//    //SI SE CAMBIA A INT SE ROMPE
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}
//
//unsigned int Render::CompilerShader(unsigned int type, const std::string& source)
//{
//    unsigned int id = glCreateShader(type);
//    const char* src = source.c_str();
//    glShaderSource(id, 1, &src, nullptr);
//    glCompileShader(id);
//
//    int result;
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//
//    if (result == GL_FALSE)
//    {
//        int length;
//        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//
//        char* message = (char*)alloca(length * sizeof(char));
//        glGetShaderInfoLog(id, length, &length, message);
//
//        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
//        std::cout << message << std::endl;
//        glDeleteShader(id);
//        return 0;
//    }
//
//    return id;
//}
//
//unsigned int Render::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//
//    unsigned int vs = CompilerShader(GL_VERTEX_SHADER, vertexShader);
//
//    unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    glAttachShader(program, vs);
//    glAttachShader(program, fs);
//
//    glLinkProgram(program);
//
//    glValidateProgram(program);
//
//    glDeleteShader(vs);
//    glDeleteShader(fs);
//
//    return program;
//}
//
//void Render::DeleteShader()
//{
//    //TO DO
//    //glDeleteProgram(shader);
//}