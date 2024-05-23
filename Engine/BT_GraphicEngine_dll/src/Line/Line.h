#ifndef LINE_H
#define LINE_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "Color/Color.h"
#include "Matrix.h"
#include "Vertexs.h"
using namespace std;

class DllApi Line
{
private:
	Renderer* renderer;

	unsigned int VAO;
	unsigned int VBO;
	vector<Vertex> vertexs;

	unsigned int locationPosition;
	unsigned int uniformModel;
	unsigned int uniformView;
	unsigned int uniformProjection;
	unsigned int uniformColor;
	unsigned int uniformAlpha;
	unsigned int uniformAffectedLight;
	unsigned int uniformUseTexture;

	void SetUniforms();
	void UpdateShader(glm::mat4 model);

public:
	Line();
	Line(Renderer* renderer);
	Line(vector<Vertex> vertexs, Renderer* renderer);
	~Line();

	void Init();
	void Draw(glm::mat4 model);
	void DeInit();

	vector<Vertex> GetVertexs();

	Color color;
};

#endif