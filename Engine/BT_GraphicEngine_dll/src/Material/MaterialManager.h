#ifndef MATERIALMANAGER_H
#define	MATERIALMANAGER_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Material/SolidMaterial.h"
#include "Material/TextureMaterial.h"
#include "Material/Material.h"

class DllApi MaterialManager
{
private:
	static SolidMaterial* solidMaterial;
	static TextureMaterial* textureMaterial;

public:
	MaterialManager();
	~MaterialManager();

	static void Init(Renderer* renderer);
	static void DeInit();

	static void SetSolidMaterial(SolidMaterial* solidMat);
	static void SetTextureMaterial(TextureMaterial* textureMat);

	static SolidMaterial* GetSolidMaterial();
	static TextureMaterial* GetTextureMaterial();
};

#endif