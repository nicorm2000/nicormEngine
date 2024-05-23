#include "Material.h"

Material::Material(Renderer* renderer)
{
	this->renderer = renderer;

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
	renderer->UpdateFloatValue(uniformShininess, shininess);
}

void Material::SetShininess(float shininess)
{
	this->shininess = shininess;
}

float Material::GetShininess()
{
	return shininess;
}