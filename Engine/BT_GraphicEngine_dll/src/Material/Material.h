#ifndef MATERIAL_H
#define MATERIAL_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Renderer/Renderer.h"
#include "glm/ext/matrix_transform.hpp"
using namespace std;

class DllApi Material
{
protected:
	Renderer* renderer;

	float shininess;

	unsigned int uniformDiffuse;
	unsigned int uniformSpecular;
	unsigned int uniformShininess;

public:
	Material(Renderer* renderer);
	~Material();

	virtual void Init() = 0;
	virtual void UpdateShader();

	void SetShininess(float shininess);
	float GetShininess();
};

#endif