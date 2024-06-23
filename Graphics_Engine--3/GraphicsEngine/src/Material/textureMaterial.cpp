#include "textureMaterial.h"

namespace MikkaiEngine
{
	TextureMaterial::TextureMaterial(Renderer* render) : Material(render)
	{
		diffuse = 0;
		specular = 0;
	}

	TextureMaterial::~TextureMaterial()
	{
	}

	void TextureMaterial::Init()
	{
		render->SetUniform(uniformDiffuse, "textureMaterial.diffuse");
		render->SetUniform(uniformSpecular, "textureMaterial.specular");
		render->SetUniform(uniformShininess, "textureMaterial.shininess");
	}

	void TextureMaterial::UpdateShader()
	{
		render->UpdateInt(uniformDiffuse, diffuse);
		render->UpdateInt(uniformSpecular, specular);
		Material::UpdateShader();
	}

	void TextureMaterial::SetDiffuse(uint diffuse)
	{
		this->diffuse = diffuse;
	}

	void TextureMaterial::SetSpecular(uint specular)
	{
		this->specular = specular;
	}

	uint TextureMaterial::GetDiffuse()
	{
		return diffuse;
	}

	uint TextureMaterial::GetSpecular()
	{
		return specular;
	}
}