#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(Renderer* renderer) : Material(renderer)
{
	diffuse = 0;
	specular = 0;
}

TextureMaterial::~TextureMaterial()
{
}

void TextureMaterial::Init()
{
	renderer->SetUniform(uniformDiffuse, "textureMaterial.diffuse");
	renderer->SetUniform(uniformSpecular, "textureMaterial.specular");
	renderer->SetUniform(uniformShininess, "textureMaterial.shininess");
}

void TextureMaterial::UpdateShader()
{
	renderer->UpdateIntValue(uniformDiffuse, diffuse);
	renderer->UpdateIntValue(uniformSpecular, specular);
	Material::UpdateShader();
}

void TextureMaterial::SetDiffuse(unsigned int diffuse)
{
	this->diffuse = diffuse;
}

void TextureMaterial::SetSpecular(unsigned int specular)
{
	this->specular = specular;
}

unsigned int TextureMaterial::GetDiffuse()
{
	return diffuse;
}

unsigned int TextureMaterial::GetSpecular()
{
	return specular;
}