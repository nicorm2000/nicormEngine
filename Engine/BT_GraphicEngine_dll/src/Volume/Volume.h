#ifndef VOLUME_H
#define	VOLUME_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Plane/Plane.h"
#include "Line/Line.h"
#include "GLM/glm.hpp"
using namespace std;

class DllApi Volume
{
public:
	Volume();
	~Volume();

	virtual void Init(Renderer* rendere) = 0;
	virtual void Draw(glm::mat4 model) = 0;
	void DeInit();

	virtual bool IsOnFrustum() = 0;
	virtual bool IsOnPlane(Plane plane) = 0;
	virtual vector<Vertex> GetVertexs() = 0;
	virtual void SetGlobalVolume(Volume* volume, glm::mat4 model) = 0;

	Line* lines;
};

#endif