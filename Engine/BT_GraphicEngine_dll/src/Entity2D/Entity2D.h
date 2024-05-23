#ifndef ENTITY2D_H
#define ENTITY2D_H

#include <glew.h>
#include <glfw3.h>
#include "Entity/Entity.h"
#include "Color/Color.h"
#include "Material/Material.h"
using namespace std;

class DllApi Entity2D : public Entity
{
protected:
	unsigned int uniformColor;
	unsigned int uniformAlpha;
	unsigned int uniformAffectedLight; 
	unsigned int uniformUseTexture;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	vector<Vertex> vertexs;
	vector<unsigned int> indexes;

	bool hasCollider;
	bool moveable;

	bool affectedLight;
	bool useTexture;

	virtual void SetUniforms() override;
	virtual void UpdateShader() override;
	void GenerateVolumeAABB();

public:
	Entity2D();
	Entity2D(Renderer* renderer);
	~Entity2D();

	void Draw();
	void DeInit();

	void SetCollider(bool hasCollider);
	void SetMoveable(bool moveable);
	void SetAffectedLight(bool affectedLight);

	bool IsMoveable();
	bool HasCollider();
	bool IsAffectedLight();

	Color color;
	Material* material;

	glm::vec3 minAABB;
	glm::vec3 maxAABB;
};

#endif