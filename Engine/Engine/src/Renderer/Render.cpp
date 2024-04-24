#include "Render.h"
#include <fstream>
#include <iostream>
#include <sstream>

Render::Render(Window* window)
{
    view = glm::mat4(0.f);
    projection = glm::mat4(0.f);

    yaw = -90.f;
    pitch = 0.f;
    sensitivity = 0.5f;
    fov = 100;

    this->window = window;

    // CAMERA POSITION
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Camera position -> vector un world space that point's to the camera's position
    cameraP = cameraPos;
    // CAMERA DIRECTION
    // For the view matrix, we want z-axis to be positive, so because (in OpenGL) the 
    // camera points towards the negative z-axis, we want to negate the direction vector
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // vector of in what direction it is pointing at
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // position vector - origin vector = camera's direction vector    

    // RIGHT AXIS
    // This represents the positive x-axis of the camera space. First we use an up vector
    // that points upwards in world space, and then we do a cross product on the up vector
    // and the direction vector. The result is a vector perpendicular to both vectors,
    // getting a vector that points in the positive x-axis's direction.
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraF = cameraFront;
    // UP AXIS
    // We take the cross product of the right and direction vector and we get the vector
    // that points to the camera's positive y-axis.
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // LOOK AT MATRIX
    // Creates a view matrix that looks at a given target (position, direction, up).
    
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    projection = glm::perspective(glm::radians(fov), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 2000.0f);
}

Render::~Render()
{
    if (window != nullptr)
    {
        window = nullptr;
        delete window;
    }
}

void Render::UpdateProjection()
{
    projection = glm::perspective(glm::radians(GetFOV()), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 2000.0f);
}

//Borrar porque no va
void Render::UpdateCameraPos(glm::vec3 pos)
{
    glm::vec3 cameraPos = glm::vec3(pos);
    cameraP = cameraPos;
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    const float radius = 5.0f;
    float a = sin(glfwGetTime()) * radius;
    float b = cos(glfwGetTime()) * radius;
    
    view = glm::lookAt(cameraPos, cameraPos + cameraF, cameraUp);
}

void Render::UpdateDirection()
{
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    SetFront(glm::normalize(direction));

    view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);
}

void Render::SetFront(glm::vec3 front)
{
    this->cameraF = front;
}

glm::vec3 Render::GetFront()
{
    return cameraF;
}

void Render::SetYaw(float yaw)
{
    this->yaw = yaw;
}

void Render::SetPitch(float pitch)
{
    this->pitch = pitch;
}

void Render::SetSensitivity(float sensitivity)
{
    this->sensitivity = sensitivity;
}

float Render::GetSensitivity()
{
    return sensitivity;
}
float Render::GetYaw()
{
    return yaw;
}

float Render::GetPitch()
{
    return pitch;
}

void Render::SetFOV(float fov)
{
    this->fov = fov;
    UpdateProjection();
}

float Render::GetFOV()
{
    return fov;
}

void Render::SetView(glm::mat4 view)
{
    this->view = view;
}

void Render::SetProjection(glm::mat4 projection)
{
    this->projection = projection;
}

void Render::SetDepth()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Render::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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