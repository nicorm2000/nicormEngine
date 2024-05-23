#include "SpotLight.h"

SpotLight::SpotLight(Render* render) : PointLight(render)
{
	direction = glm::vec3(0);
	cutOff = 0;
	outerCutOff = 0;

	uniformDirection = 0;
	uniformCutOff = 0;
	uniformOuterCutOff = 0;
}

SpotLight::~SpotLight()
{
}

void SpotLight::UseLight()
{
	UpdateShader();
}

void SpotLight::UpdateShader()
{
	PointLight::UpdateShader();
	renderer->UpdateLightVec3(uniformDirection, direction);
	renderer->UpdateLightFloat(uniformCutOff, cutOff);
	renderer->UpdateLightFloat(uniformOuterCutOff, outerCutOff);
	SetUniforms(renderer->GetShaderId());
}

void SpotLight::SetUniforms(int index)
{
	string indexSTR = to_string(index).c_str();
	renderer->SetUniform(uniformColor, ("spotLight[" + indexSTR + "].pointLight.color").c_str());
	renderer->SetUniform(uniformDirection, ("spotLight[" + indexSTR + "].direction").c_str());
	renderer->SetUniform(uniformPosition, ("spotLight[" + indexSTR + "].pointLight.position").c_str());
	renderer->SetUniform(uniformAmbient, ("spotLight[" + indexSTR + "].pointLight.ambient").c_str());
	renderer->SetUniform(uniformDiffuse, ("spotLight[" + indexSTR + "].pointLight.diffuse").c_str());
	renderer->SetUniform(uniformSpecular, ("spotLight[" + indexSTR + "].pointLight.specular").c_str());
	renderer->SetUniform(uniformConstant, ("spotLight[" + indexSTR + "].pointLight.constant").c_str());
	renderer->SetUniform(uniformLinear, ("spotLight[" + indexSTR + "].pointLight.linear").c_str());
	renderer->SetUniform(uniformQuadratic, ("spotLight[" + indexSTR + "].pointLight.quadratic").c_str());
	renderer->SetUniform(uniformCutOff, ("spotLight[" + indexSTR + "].cutOff").c_str());
	renderer->SetUniform(uniformOuterCutOff, ("spotLight[" + indexSTR + "].outerCutOff").c_str());
	renderer->SetUniform(uniformEnabled, ("spotLight[" + indexSTR + "].enabled").c_str());
}

void SpotLight::SetDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void SpotLight::SetCutOff(float cutOff)
{
	this->cutOff = cos(glm::radians(cutOff));
}

void SpotLight::SetOuterCutOff(float outerCutOff)
{
	this->outerCutOff = cos(glm::radians(outerCutOff));
}

glm::vec3 SpotLight::GetDirection()
{
	return direction;
}

float SpotLight::GetCutOff()
{
	return cutOff;
}

float SpotLight::GetOuterCutOff()
{
	return outerCutOff;
}