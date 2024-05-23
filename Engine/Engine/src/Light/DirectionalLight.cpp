#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Render* renderer) : Light(renderer)
{
	direction = glm::vec3(0);

	uniformDirection = 0;
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::UseLight()
{
	UpdateShader();
}

void DirectionalLight::UpdateShader()
{
	Light::UpdateShader();
	renderer->UpdateLightVec3(uniformDirection, direction);
	SetUniforms();
}

void DirectionalLight::SetUniforms()
{
	renderer->SetUniform(uniformColor, "directionalLight.color");
	renderer->SetUniform(uniformDirection, "directionalLight.direction");
	renderer->SetUniform(uniformAmbient, "directionalLight.ambient");
	renderer->SetUniform(uniformDiffuse, "directionalLight.diffuse");
	renderer->SetUniform(uniformSpecular, "directionalLight.specular");
	renderer->SetUniform(uniformEnabled, "directionalLight.enabled");
}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

glm::vec3 DirectionalLight::GetDirection()
{
	return direction;
}