#ifndef SOLID_MATERIAL_H
#define SOLID_MATERIAL_H

#include <glew.h>
#include <glfw3.h>
#include "Material/Material.h"
using namespace std;

class DllApi SolidMaterial : public Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	unsigned int uniformAmbient;

public:
	SolidMaterial(Renderer* renderer);
	~SolidMaterial();

	void Init() override;
	void UpdateShader() override;

	void SetAmbient(glm::vec3 ambient);
	void SetDiffuse(glm::vec3 diffuse);
	void SetSpecular(glm::vec3 specular);

	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
};

#endif