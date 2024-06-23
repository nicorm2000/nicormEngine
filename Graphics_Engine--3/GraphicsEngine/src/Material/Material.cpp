#include "Material.h"
namespace MikkaiEngine
{

	Material::Material(Renderer* render)
	{
		this->render = render;

		shininess = 0.f;

		uniformDiffuse = 0;
		uniformSpecular = 0;
		uniformShininess = 0;
	}

	Material::~Material()
	{
	}

	void Material::UpdateShader()
	{
		render->UpdateFloatValue(uniformShininess, shininess);
	}

	void Material::SetShininess(float shininess)
	{
		this->shininess = shininess;
	}

	float Material::GetShininess()
	{
		return shininess;
	}

}