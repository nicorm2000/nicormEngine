#ifndef MODEL_H
#define MODEL_H

#include "Mesh2/Mesh2.h"
#include "Entity2/Entity2.h"
using namespace std;
namespace MikkaiEngine
{
	class GraficosEngine_API Model
	{
	public:
		Model(Renderer* rend);
		~Model();
		Entity2* GetBaseNode() { return baseNode; };
		Renderer* GetRender() { return shader; };

		void SetBaseNode(Entity2* v) { baseNode = v; };
		void Draw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	protected:
		// model data 
		string          directory;
		Entity2* baseNode;
		Renderer* shader;

	};
}

#endif