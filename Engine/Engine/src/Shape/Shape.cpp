#include "Shape.h"

Shape::Shape(Render* newRenderer) : Entity2D()
{
    renderer = newRenderer;
}

Shape::~Shape()
{
    DetachMaterial();
    renderer->UnBindVertex(VAO, VBO, EBO);
}

void Shape::SetColor(glm::vec3 newColor)
{
	colorVector = newColor;
}

glm::vec3 Shape::GetColor()
{
	return colorVector;
}

void Shape::AttachMaterial()
{
    renderer->GetMaterial()->UseMaterial();
    renderer->GetMaterial()->ModifyMaterial(renderer->GetProjectionMatrix(), renderer->GetViewMatrix(), GetModelMatrix(), colorVector);
}

void Shape::DetachMaterial()
{
    renderer->GetMaterial()->DeleteMaterial();
}

void Shape::Draw()
{
    AttachMaterial();
    renderer->DrawWithIndexBuffer(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, VAO);
}

void Shape::CreateTriangle()
{
    float positions[] =
    {
        // Positions         // Colors
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // Lower-left corner  
         0.0f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // Lower-right corner
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f  // Top-center corner
    };

    unsigned int indices[] =
    {
        0, 1, 2,
    };

    renderer->CreateBuffers(VAO, VBO, EBO);
    renderer->BindBuffers(TRIANGLE_POSITIONS_ARRAY_COUNT * sizeof(float), TRIANGLE_INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
    renderer->EnableVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, 0); //pos
    renderer->EnableVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 3)); //color
}

void Shape::CreateSquare()
{
    float positions[] = 
    {
        // Positions         // Colors
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // Top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // Bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, // Bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f  // Top left
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    renderer->CreateBuffers(VAO, VBO, EBO);
    renderer->BindBuffers(SQUARE_POSITIONS_ARRAY_COUNT * sizeof(float), SQUARE_INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
    renderer->EnableVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, 0); //pos
    renderer->EnableVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 3)); //color
}