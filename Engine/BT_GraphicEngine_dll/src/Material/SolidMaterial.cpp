#include  "SolidMaterial.h"

SolidMaterial::SolidMaterial(Renderer* renderer) : Material(renderer)
{
	ambient = glm::vec3(0.f);
	diffuse = glm::vec3(0.f);
	specular = glm::vec3(0.f);

	uniformAmbient = 0;
}

SolidMaterial::~SolidMaterial()
{
}

void SolidMaterial::Init()
{
	renderer->SetUniform(uniformAmbient, "baseMaterial.ambient");
	renderer->SetUniform(uniformDiffuse, "baseMaterial.diffuse");
	renderer->SetUniform(uniformSpecular, "baseMaterial.specular");
	renderer->SetUniform(uniformShininess, "baseMaterial.shininess");
} 

void SolidMaterial::UpdateShader()
{
	renderer->UpdateVec3(uniformAmbient, ambient);
	renderer->UpdateVec3(uniformDiffuse, diffuse);
	renderer->UpdateVec3(uniformSpecular, specular);
	Material::UpdateShader();
}

void SolidMaterial::SetAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void SolidMaterial::SetDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void SolidMaterial::SetSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

glm::vec3 SolidMaterial::GetAmbient()
{
	return ambient;
}

glm::vec3 SolidMaterial::GetDiffuse()
{
	return diffuse;
}

glm::vec3 SolidMaterial::GetSpecular()
{
	return specular;
}