#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "export.h"
#include "Entity/Entity.h"
#include "Color/Color.h"
#include "glm/ext/matrix_transform.hpp"
using namespace std;

class DllApi Light : public Entity
{
protected:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	bool enabled;

	unsigned int uniformColor;
	unsigned int uniformAmbient;
	unsigned int uniformDiffuse;
	unsigned int uniformSpecular;
	unsigned int uniformEnabled;

	virtual void UpdateShader() override;

public:
	Light(Render* renderer);
	~Light();

	virtual void UseLight();

	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);
	void SetEnabled(bool enabled);

	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	bool IsEnabled();

	Color color;
};

#endif