#ifndef MATERIAL_H
#define MATERIAL_H

#include "Exports/Exports.h"

#include "Renderer/renderer.h"

#include "GLM/ext/matrix_transform.hpp"

namespace MikkaiEngine
{
	class GraficosEngine_API Material
	{
	public:
		Material(Renderer* render);
		~Material();

		virtual void Init() = 0;
		virtual void UpdateShader();

		void SetShininess(float shininess);
		float GetShininess();

	protected:
		Renderer* render;

		float shininess;

		uint uniformDiffuse;
		uint uniformSpecular;
		uint uniformShininess;
	};
}

#endif // !MATERIAL_H
