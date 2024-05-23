#include "Mesh.h"

Mesh::Mesh()
{
	renderer = nullptr;

	material = nullptr;
	color = Color();

	vertexs = vector<Vertex>();
	indexes = vector<unsigned int>();
	textures = vector<Texture>();

	VAO = 0;
	VBO = 0;
	EBO = 0;

	uniformColor = 0;
	uniformAlpha = 0;
	uniformBaseTexture = 0;
	uniformUseTexture = 0;

	locationPosition = 0;
	locationNormal = 0;
	locationTexCoord = 0;
}

Mesh::Mesh(Renderer* renderer, vector<Vertex> vertexs, vector<unsigned int> indexes, vector<Texture> textures)
{
	this->renderer = renderer;

	material = nullptr;
	color = Color();

	this->vertexs = vertexs;
	this->indexes = indexes;
	this->textures = textures;

	VAO = 0;
	VBO = 0;
	EBO = 0;

	uniformColor = 0;
	uniformAlpha = 0;
	uniformBaseTexture = 0;
	uniformUseTexture = 0;

	locationPosition = 0;
	locationNormal = 0;
	locationTexCoord = 0;
}

Mesh::~Mesh()
{
}

void Mesh::Init()
{
	SetUniforms();

	renderer->GenBuffers(VAO, VBO, EBO);

	if (vertexs.size() == 0)
	{
		renderer->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), 0);
	}
	else
	{
		renderer->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
	}

	if (indexes.size() == 0)
	{
		renderer->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), 0);
	}
	else
	{
		renderer->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);
	}

	renderer->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
	renderer->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	renderer->SetBaseAttribs(locationTexCoord, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}

void Mesh::Draw()
{
	for (int i = 0; i < textures.size(); i++)
	{
		renderer->UseTexture(i, textures[i].ID);
	}

	UpdateShader();

	renderer->Draw(VAO, indexes.size());

	renderer->CleanTexture();
}

void Mesh::DeInit()
{
	renderer->UnBind(VAO, VBO, EBO);

	if (textures.size() > 0)
	{
		//renderer->TextureDelete(uniformBaseTexture, mesh.textures[0].id);
	}

	vertexs.clear();
	indexes.clear();
	textures.clear();
}

std::vector<Vertex> Mesh::GetVertexs()
{
	return vertexs;
}

void Mesh::SetUniforms()
{
	renderer->SetUniform(uniformColor, "color");
	renderer->SetUniform(uniformAlpha, "a");
	renderer->SetUniform(uniformBaseTexture, "baseTexture");
	renderer->SetUniform(uniformUseTexture, "useTexture");

	renderer->SetLocation(locationPosition, "aPos");
	renderer->SetLocation(locationNormal, "aNor");
	renderer->SetLocation(locationTexCoord, "aTex");
}

void Mesh::UpdateShader()
{
	renderer->UpdateStatus(uniformUseTexture, textures.size() > 0);

	if (textures.size() > 0)
	{
		renderer->UpdateTexture(uniformBaseTexture, textures[0].ID);
	}

	if (material != nullptr)
	{
		material->UpdateShader();
	}

	renderer->UpdateColor(uniformColor, uniformAlpha, color.GetColorRGBA());
}