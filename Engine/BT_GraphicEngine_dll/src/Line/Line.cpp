#include "Line.h"

Line::Line()
{
	renderer = nullptr;
	color = Color(125, 255, 0, 1);

	VAO = 0;
	VBO = 0;

	vertexs = vector<Vertex>();

	locationPosition = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformProjection = 0;
	uniformColor = 0;
	uniformAlpha = 0;
	uniformAffectedLight = 0;
	uniformUseTexture = 0;
}

Line::Line(Renderer* renderer)
{
	this->renderer = renderer;
	color = Color(125, 255, 0, 1);

	VAO = 0;
	VBO = 0;

	vertexs = vector<Vertex>();

	locationPosition = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformProjection = 0;
	uniformColor = 0;
	uniformAlpha = 0;
	uniformAffectedLight = 0;
	uniformUseTexture = 0;
}

Line::Line(vector<Vertex> vertexs, Renderer* renderer)
{
	this->renderer = renderer;
	this->vertexs = vertexs;

	color = Color(125, 255, 0, 1);

	VAO = 0;
	VBO = 0;

	locationPosition = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformProjection = 0;
	uniformColor = 0;
	uniformAlpha = 0;
	uniformAffectedLight = 0;
	uniformUseTexture = 0;
}

Line::~Line()
{
}

void Line::Init()
{
	SetUniforms();

	renderer->GenBuffers(VAO, VBO);
	renderer->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);

	renderer->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
}

void Line::Draw(glm::mat4 model)
{
	renderer->UseShader();
	UpdateShader(model);
	renderer->DrawLines(VAO, vertexs.size());
	renderer->CleanShader();
}

void Line::DeInit()
{
	renderer->UnBind(VAO, VBO);
	vertexs.clear();
}

vector<Vertex> Line::GetVertexs()
{
	return vertexs;
}

void Line::SetUniforms()
{
	renderer->SetLocation(locationPosition, "aPos");

	renderer->SetUniform(uniformModel, "model");
	renderer->SetUniform(uniformView, "view");
	renderer->SetUniform(uniformProjection, "projection");

	renderer->SetUniform(uniformColor, "color");
	renderer->SetUniform(uniformAlpha, "a");

	renderer->SetUniform(uniformAffectedLight, "affectedLight");
	renderer->SetUniform(uniformUseTexture, "useTexture");
}

void Line::UpdateShader(glm::mat4 model)
{
	renderer->UpdateMVP(uniformModel, uniformView, uniformProjection, model);
	renderer->UpdateColor(uniformColor, uniformAlpha, color.GetColorRGBA());
	renderer->UpdateStatus(uniformAffectedLight, false);
	renderer->UpdateStatus(uniformUseTexture, false);
}