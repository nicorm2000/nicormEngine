#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Light/PointLight.h"
using namespace std;

class DllApi SpotLight : public PointLight
{
private:
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	unsigned int uniformDirection;
	unsigned int uniformCutOff;
	unsigned int uniformOuterCutOff;

	void UpdateShader() override;
	void SetUniforms(int index) override;

public:
	SpotLight(Renderer* renderer);
	~SpotLight();

	void UseLight() override;

	void SetDirection(glm::vec3 direction);
	void SetCutOff(float cutOff);
	void SetOuterCutOff(float outerCutOff);

	glm::vec3 GetDirection();
	float GetCutOff();
	float GetOuterCutOff();
};

#endif