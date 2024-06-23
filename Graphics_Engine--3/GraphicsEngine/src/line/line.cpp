#include "line.h"

namespace MikkaiEngine
{

	Line::Line(Renderer* render)
	{
		this->render = render;
		color = glm::vec3(124, 252, 0);

		VAO = 0;
		VBO = 0;
		EBO = 0;

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();

		locationPosition = 0;
		locationNormal = 0;
		uniformColor = 0;
		uniformAlpha = 0;
	}

	Line::Line(std::vector<Vertex> vertexs, Renderer* render)
	{
		this->render = render;
		this->vertexs = vertexs;
		indexes = std::vector<uint>();

		color = glm::vec3(124, 252, 0);

		VAO = 0;
		VBO = 0;
		EBO = 0;

		locationPosition = 0;
		locationNormal = 0;
		uniformColor = 0;
		uniformAlpha = 0;
	}

	Line::~Line()
	{
	}

	void Line::Init()
	{
		SetUniforms();

		for (int i = 0; i < 8; i++)
		{
			indexes.push_back(i);
		}

		render->GenBuffers(VAO, VBO, EBO);
		render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
		render->BindIndexes(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	}

	void Line::Draw()
	{
		UpdateShader();
		render->DrawLines(VAO, indexes.size());
	}

	void Line::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);

		vertexs.clear();
		indexes.clear();
	}

	void Line::SetVertexs(std::vector<Vertex> vertexs)
	{
		this->vertexs = vertexs;

		UpdateVertexs();
	}

	std::vector<Vertex> Line::GetVertexs()
	{
		return vertexs;
	}

	void Line::UpdateVertexs()
	{
		render->reBindBuffer(VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
	}

	void Line::SetUniforms()
	{
		render->SetLocation(locationPosition, "aPos");
		render->SetLocation(locationNormal, "aNor");

		render->SetUniform(uniformColor, "color");
	}

	void Line::UpdateShader()
	{
		render->UpdateColor(uniformColor, color);
	}
}