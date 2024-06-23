#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include "Material/material.h"

namespace MikkaiEngine
{
	class GraficosEngine_API TextureMaterial : public Material
	{
	public:
		TextureMaterial(Renderer* render);
		~TextureMaterial();

		void Init() override;
		void UpdateShader() override;

		void SetDiffuse(uint diffuse);
		void SetSpecular(uint specular);

		uint GetDiffuse();
		uint GetSpecular();

	private:
		uint diffuse;
		uint specular;
	};
}

#endif // !TEXTURE_MATERIAL_H
