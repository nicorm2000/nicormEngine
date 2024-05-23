#include "Shape.h"

Shape::Shape() : Entity2D()
{
}

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
}

Shape::~Shape()
{
}

void Shape::Init(SHAPE_TYPE shapeType)
{
	useTexture = false;
	SetUniforms();

	switch (shapeType)
	{
	case SHAPE_TYPE::TRIANGLE:
		for (int i = 0; i < triangVertexTam; i++)
		{
			Vertex vertex;
			vertex.Position = triangPositions[i];
			vertex.Normal = triangNormals[i];
			vertexs.push_back(vertex);
		}
		for (int i = 0; i < triangIndexTam; i++)
		{
			indexes.push_back(triangIndexes[i]);
		}
		break;

	case SHAPE_TYPE::QUAD:
		for (int i = 0; i < quadVertexTam; i++)
		{
			Vertex vertex;
			vertex.Position = quadPositions[i];
			vertex.Normal = quadNormals[i];
			vertexs.push_back(vertex);
		}
		for (int i = 0; i < quadIndexTam; i++)
		{
			indexes.push_back(quadIndexes[i]);
		}
		break;

	case SHAPE_TYPE::CUBE:
		for (int i = 0; i < cubeVertexTam; i++)
		{
			Vertex vertex;
			vertex.Position = cubePositions[i];
			vertex.Normal = cubeNormals[i];
			vertexs.push_back(vertex);
		}
		for (int i = 0; i < cubeIndexTam; i++)
		{
			indexes.push_back(cubeIndexes[i]);
		}
		break;

	default:
		return;
	}

	renderer->GenBuffers(VAO, VBO, EBO);
	renderer->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
	renderer->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

	renderer->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
	renderer->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	localVolume = new VolumeAABB();
	localVolume->Init(renderer);
	GenerateVolumeAABB();
}

void Shape::Draw()
{
	if (IsCanDraw())
	{
		renderer->UseShader();
		renderer->BlendEnable();

		UpdateShader();
		Entity2D::Draw();

		renderer->BlendDisable();
		renderer->CleanShader();

		Entity::DrawVolume();
	}
	else
	{
		cout << "DONT DRAW: " << name << endl;
	}

	Entity::Draw();
}

void Shape::DeInit()
{
	renderer->UnBind(VAO, VBO, EBO);
	Entity2D::DeInit();
}