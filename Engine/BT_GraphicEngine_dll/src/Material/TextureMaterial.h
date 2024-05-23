#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include <glew.h>
#include <glfw3.h>
#include "Material/Material.h"
using namespace std;

class DllApi TextureMaterial : public Material
{
private:
	unsigned int diffuse;
	unsigned int specular;

public:
	TextureMaterial(Renderer* renderer);
	~TextureMaterial();

	void Init() override;
	void UpdateShader() override;

	void SetDiffuse(unsigned int diffuse);
	void SetSpecular(unsigned int specular);

	unsigned int GetDiffuse();
	unsigned int GetSpecular();
};

#endif