#ifndef MATERIAL_MANAGER_H
#define	MATERIAL_MANAGER_H

#include "Exports/Exports.h"

#include "Material/solidMaterial.h"
#include "Material/textureMaterial.h"

namespace MikkaiEngine
{
	class GraficosEngine_API MaterialManager
	{
	public:
		MaterialManager();
		~MaterialManager();

		static void Init(Renderer* render);
		static void DeInit();

		static void SetSolidMaterial(SolidMaterial* solidMat);
		static void SetTextureMaterial(TextureMaterial* textureMat);

		static SolidMaterial* GetSolidMaterial();
		static TextureMaterial* GetTextureMaterial();

	private:
		static SolidMaterial* solidMaterial;
		static TextureMaterial* textureMaterial;
	};
}

#endif