#include "Sprite.h"

Sprite::Sprite() : Entity2D()
{
    animation = nullptr;
    renderer = nullptr;
}

Sprite::Sprite(Render* newRenderer, std::string path) : Entity2D()
{
    animation = nullptr;
    renderer = newRenderer;
    texture = TextureImporter::LoadTexture(path, true);

    widthTexture = texture.width;
    heightTexture = texture.height;

    float positions[] =
    {
        // Positions         // Colors          // Texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // Top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // Bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // Top left
    };

    /* Index buffer */
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    renderer->CreateBuffers(VAO, VBO, EBO);
    renderer->BindBuffers(POSITIONS_ARRAY_COUNT * sizeof(float), INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
    renderer->EnableVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, 0); //pos
    renderer->EnableVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 3)); //color
    renderer->EnableVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 6)); //texture coords
}

Sprite::~Sprite()
{
    DetachMaterial();

    if (animation != nullptr)
    {
        animation = nullptr;
        delete animation;
    }
}

void Sprite::AttachMaterial()
{
    renderer->GetMaterial()->UseMaterial();
    renderer->GetMaterial()->ModifyMaterial(renderer->GetProjectionMatrix(), renderer->GetViewMatrix(), GetModelMatrix(), colorVector, texture.ID);
}

void Sprite::DetachMaterial()
{
    renderer->GetMaterial()->DeleteMaterial();
}

void Sprite::Draw()
{
    AttachMaterial();
    renderer->BindTexture(GL_TEXTURE_2D, texture.ID);
    renderer->DrawWithIndexBuffer(GL_TRIANGLES, VERTEX_SIZE, GL_UNSIGNED_INT, nullptr, VAO);
}

void Sprite::AddFrames(int rows, int cols)
{
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            animation->AddFrame(x, y, widthTexture / cols, heightTexture / rows, widthTexture, heightTexture, 1);
        }
    }
}

void Sprite::AddFrame(float frameX, float frameY, int rows, int cols)
{
    animation->AddFrame(frameX, frameY, widthTexture / cols, heightTexture / rows, widthTexture, heightTexture, 1);
}

void Sprite::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight)
{
    animation->AddFrame(frameX, frameY, frameWidth, frameHeight, textureWidth, textureHeight, 1);
}

void Sprite::UpdateAnimation()
{
    if (!animation)
    {
        return;
    }
    else
    {
        animation->Update();
        SetUVCoords(animation->GetFrames()[animation->GetCurrentFrame()]);
    }
}

void Sprite::UpdateAnimation(Animation* animation)
{
    animation->Update();
    SetUVCoords(animation->GetFrames()[animation->GetCurrentFrame()]);
}

void Sprite::SetAnimation(Animation* animation)
{
    this->animation = animation;
}

void Sprite::LoadTexture(std::string path, bool invertImage)
{
    texture = TextureImporter::LoadTexture(path, invertImage);

    widthTexture = texture.width;
    heightTexture = texture.height;

    float positions[] =
    {
        // Positions         // Colors          // Texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, // Top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, // Bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f, // Bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f  // Top left
    };

    /* Index buffer */
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    renderer->CreateBuffers(VAO, VBO, EBO);
    renderer->BindBuffers(POSITIONS_ARRAY_COUNT * sizeof(float), INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
    renderer->EnableVertexAttributes(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, 0); //pos
    renderer->EnableVertexAttributes(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 3)); //color
    renderer->EnableVertexAttributes(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERTEX_SIZE, (void*)(sizeof(float) * 6)); //texture coords
}

void Sprite::SetUVCoords(Frame frame)
{
    float coords[8] =
    {
        frame.GetUVCoords()[0].U, frame.GetUVCoords()[0].V,
        frame.GetUVCoords()[1].U, frame.GetUVCoords()[1].V,
        frame.GetUVCoords()[2].U, frame.GetUVCoords()[2].V,
        frame.GetUVCoords()[3].U, frame.GetUVCoords()[3].V
    };

    float positions[] =
    {
        // Positions         // Colors          // Texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[6], coords[7], // Top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[2], coords[3], // Bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[0], coords[1], // Bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[4], coords[5]  // Top left
    };

    /* Index buffer */
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    renderer->BindBuffers(POSITIONS_ARRAY_COUNT * sizeof(float), INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
}

void Sprite::SetTextureCoords(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4)
{
    float coords[]
    {
        u1, v1,
        u2, v2,
        u3, v3,
        u4, v4
    };

    float positions[] =
    {
        // Positions         // Colors          // Texture coords
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[6], coords[7], // Top right
         0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[2], coords[3], // Bottom right
        -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[0], coords[1], // Bottom left
        -0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 1.0f, coords[4], coords[5]  // Top left
    };

    positions[6] = coords[0];
    positions[14] = coords[2];
    positions[22] = coords[4];
    positions[30] = coords[6];

    positions[7] = coords[1];
    positions[15] = coords[3];
    positions[23] = coords[5];
    positions[31] = coords[7];

    /* Index buffer */
    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    renderer->BindBuffers(POSITIONS_ARRAY_COUNT * sizeof(float), INDEX_ARRAY_COUNT * sizeof(unsigned int), positions, indices, VAO, VBO, EBO);
}

void Sprite::SetColor(glm::vec3 newColor)
{
    colorVector = newColor;
}

glm::vec3 Sprite::GetColor()
{
    return colorVector;
}