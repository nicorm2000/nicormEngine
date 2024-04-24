#ifndef ENTITY3D_H
#define ENTITY3D_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include <vector>
#include <string>
#include "Entity/Entity.h"
//#include "Mesh/Mesh.h"

using namespace std;

class DllApi Entity3D : public Entity
{
protected:
	//vector<Mesh*> meshes;

	unsigned int uniformAffectedLight;

	bool affectedLight;

	virtual void SetUniforms() override;
	virtual void UpdateShader() override;
	void GenerateVolumeAABB();

public:
	Entity3D();
	Entity3D(Render* renderer);
	//Entity3D(vector<Mesh*> meshes, Renderer* renderer);
	~Entity3D();

	void Init();
	void Draw();
	void DeInit();

	//glm::vec3 minAABB;
	//glm::vec3 maxAABB;
};

#endif