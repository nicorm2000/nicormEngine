#include "Light.h"

Light::Light(Renderer* renderer) : Entity(renderer)
{
	color = Color();

	ambient = glm::vec3(0);
	diffuse = glm::vec3(0);
	specular = glm::vec3(0);
	enabled = true;

	uniformColor = 0;
	uniformAmbient = 0;
	uniformDiffuse = 0;
	uniformSpecular = 0;
	uniformEnabled = 0;
}

Light::~Light()
{
}

void Light::UseLight()
{
	UpdateShader();
}

void Light::UpdateShader()
{
	renderer->UseShader();
	Entity::UpdateShader();
	renderer->UpdateLightVec3(uniformColor, color.GetColorRGB());
	renderer->UpdateLightVec3(uniformAmbient, ambient);
	renderer->UpdateLightVec3(uniformDiffuse, diffuse);
	renderer->UpdateLightVec3(uniformSpecular, specular);
	renderer->UpdateLightStatus(uniformEnabled, enabled);
}

void Light::SetAmbient(glm::vec3 ambient)
{
	this->ambient = ambient;
}

void Light::SetDiffuse(glm::vec3 diffuse)
{
	this->diffuse = diffuse;
}

void Light::SetSpecular(glm::vec3 specular)
{
	this->specular = specular;
}

void Light::SetEnabled(bool enabled)
{
	this->enabled = enabled;
}

glm::vec3 Light::GetAmbient()
{
	return ambient;
}

glm::vec3 Light::GetDiffuse()
{
	return diffuse;
}

glm::vec3 Light::GetSpecular()
{
	return specular;
}

bool Light::IsEnabled()
{
	return enabled;
}