#include "Entity2D.h"
namespace MikkaiEngine
{
	void Entity2D::Draw()
	{
		_renderer->UseTexture(false);
		_renderer->UseMaterial(false);
		_renderer->UpdateColor(_uniformColor, _color);
		_renderer->UpdateMVP(getTransform()->getWorldModel());	
		_renderer->Draw(_VAO, _VBO, _EBO, vertices, tam, vertexs);
	}

	Entity2D::Entity2D(Renderer* render) : Entity2(render)
	{
		_material = nullptr;

		_VAO = 0;
		_VBO = 0;
		_EBO = 0;
		tam = 0;
		vertexs = 0;
		vertices = 0;
	}

	Entity2D::~Entity2D()
	{
	}


	void Entity2D::SetUniforms()
	{
		Entity2::SetUniforms();
	}
}