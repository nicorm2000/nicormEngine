#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include "Light/Light.h"
using namespace std;

class DllApi DirectionalLight : public Light
{
private:
	glm::vec3 direction;

	unsigned int uniformDirection;

	void UpdateShader() override;
	void SetUniforms();

public:
	DirectionalLight(Render* renderer);
	~DirectionalLight();

	void UseLight() override;

	void SetDirection(glm::vec3 direction);
	glm::vec3 GetDirection();
};

#endif