#include "pointLight.h"
namespace MikkaiEngine
{
	std::list<PointLight*> PointLight::PointLightLists;
	int PointLight::quantity =0;
	uint PointLight::_uniformPointLightsQuantity;
	PointLight::PointLight(Renderer* render) : Light(render)
	{

		constant = 0;
		linear = 0;
		quadratic = 0;

		_uniformPosition = 0;
		_uniformConstant = 0;
		_uniformLinear = 0;
		_uniformQuadratic = 0;
		PointLightLists.push_back(this);
	}
	void PointLight::Init()
	{
		setName("pointLight[" + std::to_string(quantity) + "]");
		quantity++;
		SetUniforms(getName());
	}

	void PointLight::SetUniforms(std::string name)
	{
		_renderer->SetUniform(_uniformPointLightsQuantity, "spotLightCuantity");
		_renderer->UpdateInt(_uniformPointLightsQuantity, quantity);
		Light::SetUniforms(name);
		_renderer->SetUniform(_uniformPosition, (name + ".position").c_str());
		_renderer->SetUniform(_uniformConstant, (name + ".constant").c_str());
		_renderer->SetUniform(_uniformLinear, (name + ".linear").c_str());
		_renderer->SetUniform(_uniformQuadratic, (name + ".quadratic").c_str());
	}

	void PointLight::UpdateLight()
	{
		Light::UpdateLight();
		pos = getPos();
		_renderer->UseShader();
		_renderer->UpdateVec3(_uniformPosition, pos);
		_renderer->UpdateFloatValue(_uniformConstant, constant);
		_renderer->UpdateFloatValue(_uniformLinear, linear);
		_renderer->UpdateFloatValue(_uniformQuadratic, quadratic);
		_renderer->CleanShader();
	}

	PointLight::~PointLight()
	{
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
	void PointLight::SetQuantityLights(int quantity)
	{
		this->quantity = quantity;
	}
}
