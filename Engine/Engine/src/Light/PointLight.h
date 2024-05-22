#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include <string>
#include "Light/Light.h"
using namespace std;

class DllApi PointLight : public Light
{
protected:
	float constant;
	float linear;
	float quadratic;

	unsigned int uniformPosition;
	unsigned int uniformConstant;
	unsigned int uniformLinear;
	unsigned int uniformQuadratic;

	virtual void UpdateShader() override;
	virtual void SetUniforms(int index);

public:
	PointLight(Render* renderer);
	~PointLight();

	void UseLight() override;

	void SetConstant(float constant);
	void SetLinear(float linear);
	void SetQuadratic(float quadratic);

	float GetConstant();
	float GetLinear();
	float GetQuadratic();
};

#endif