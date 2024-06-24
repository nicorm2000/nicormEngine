#include "DirectionalLight.h"
namespace MikkaiEngine
{
	std::list<DirectionLight*> DirectionLight::DirectionLightLists;

	DirectionLight::DirectionLight(Renderer* render) : Light(render)
	{
		direction = glm::vec3(0);
		_uniformDirection = 0;
		DirectionLightLists.push_front(this);
	}

	void DirectionLight::Init()
	{
		setName("directionalLight");
		SetUniforms(getName());
	}
	void DirectionLight::SetUniforms(std::string name)
	{
		_renderer->SetUniform(_uniformDirection, (name + ".direction").c_str());
		Light::SetUniforms(name);
	}

	void DirectionLight::UpdateLight()
	{

		Light::UpdateLight();
		_renderer->UseShader();
		_renderer->UpdateVec3(_uniformDirection, direction);
		if (!getactive())
			_renderer->UpdateVec3(_uniformDirection, vec3(0,0,0));
		_renderer->CleanShader();
	}

	DirectionLight::~DirectionLight()
	{
		direction = glm::vec3(0);
		_uniformDirection = 0;
	}

	void DirectionLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}
	glm::vec3 DirectionLight::GetDirection()
	{
		return direction;
	}
}