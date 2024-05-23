#include "PointLight.h"

PointLight::PointLight(Renderer* render) : Light(render)
{
	constant = 0;
	linear = 0;
	quadratic = 0;

	uniformPosition = 0;
	uniformConstant = 0;
	uniformLinear = 0;
	uniformQuadratic = 0;
}

PointLight::~PointLight()
{
}

void PointLight::UseLight()
{
	UpdateShader();
}

void PointLight::UpdateShader()
{
	Light::UpdateShader();
	renderer->UpdateLightVec3(uniformPosition, transform.position);
	renderer->UpdateLightFloat(uniformConstant, constant);
	renderer->UpdateLightFloat(uniformLinear, linear);
	renderer->UpdateLightFloat(uniformQuadratic, quadratic);
	SetUniforms(renderer->GetShaderId());
}

void PointLight::SetUniforms(int index)
{
	string indexSTR = to_string(index).c_str();
	renderer->SetUniform(uniformColor, ("pointLight[" + indexSTR + "].color").c_str());
	renderer->SetUniform(uniformPosition, ("pointLight[" + indexSTR + "].position").c_str());
	renderer->SetUniform(uniformAmbient, ("pointLight[" + indexSTR + "].ambient").c_str());
	renderer->SetUniform(uniformDiffuse, ("pointLight[" + indexSTR + "].diffuse").c_str());
	renderer->SetUniform(uniformSpecular, ("pointLight[" + indexSTR + "].specular").c_str());
	renderer->SetUniform(uniformConstant, ("pointLight[" + indexSTR + "].constant").c_str());
	renderer->SetUniform(uniformLinear, ("pointLight[" + indexSTR + "].linear").c_str());
	renderer->SetUniform(uniformQuadratic, ("pointLight[" + indexSTR + "].quadratic").c_str());
	renderer->SetUniform(uniformEnabled, ("pointLight[" + indexSTR + "].enabled").c_str());
}

void PointLight::SetConstant(float constant)
{
	this->constant = constant;
}

void PointLight::SetLinear(float linear)
{
	this->linear = linear;
}

void PointLight::SetQuadratic(float quadratic)
{
	this->quadratic = quadratic;
}

float PointLight::GetConstant()
{
	return constant;
}

float PointLight::GetLinear()
{
	return linear;
}

float PointLight::GetQuadratic()
{
	return quadratic;
}