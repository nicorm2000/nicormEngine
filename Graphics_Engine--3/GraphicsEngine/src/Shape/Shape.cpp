#include "shape.h"
namespace MikkaiEngine
{

	Shape::Shape(Renderer* render) : Entity2D(render)
	{
	}

	Shape::~Shape()
	{
	}

	void Shape::Init(SHAPE_TYPE shapeType)
	{
		SetUniforms();

		uint* indexes;

		switch (shapeType)
		{
		case SHAPE_TYPE::TRIANGLE:

			indexes = triangIndexes;
			vertices = triangIndexTam;
			vertexs = triangVertex;
			tam = sizeof(vertexs) * triangVertTam;

			break;
		case SHAPE_TYPE::QUAD:

			indexes = quadIndexes;
			vertices = quadIndexTam;
			vertexs = quadVertex;
			tam = sizeof(vertexs) * quadVertTam;

			break;
		case SHAPE_TYPE::CUBE:

			indexes = cubeIndexes;
			vertices = cubeIndexTam;
			vertexs = cubeVertex;
			tam = sizeof(vertexs) * cubeVertTam;

			break;
		default:
			return;
		}

		_renderer->GenBuffers(_VAO, _VBO, _EBO);
		_renderer->BindBuffer(_VAO, _VBO, tam, vertexs);
		_renderer->BindIndexes(_EBO, sizeof(indexes) * vertices, indexes);

		_renderer->SetBaseAttribs(_locationPosition, 3, 6, 0);
		_renderer->SetBaseAttribs(_locationNormal, 3, 6, 3);
	}

	void Shape::Draw()
	{
		_renderer->UseShader();
		Entity2D::Draw();
		_renderer->CleanShader();
	}

	void Shape::DeInit()
	{
		_renderer->UnBind(_VAO, _VBO, _EBO);
	}
}