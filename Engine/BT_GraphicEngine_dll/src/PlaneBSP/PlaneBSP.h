#ifndef PLANE_BSP_H
#define PLANE_BSP_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Plane/plane.h"
#include "Shape/Shape.h"
#include "Material/MaterialManager.h"
using namespace std;

class DllApi PlaneBSP
{
private:
	bool canDraw;

public:
	PlaneBSP();
	~PlaneBSP();

	void Init(Renderer* renderer, Entity* node, glm::vec3 position, glm::vec3 normal);

	void SwitchCanDrawStatus();
	bool SamePositionsSide(glm::vec3 point1, glm::vec3 point2);

	Entity* node;
	Plane* plane;

};

#endif