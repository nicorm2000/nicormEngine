#include "PlaneBSP.h"

PlaneBSP::PlaneBSP()
{
	plane = nullptr;
	node = nullptr;
	canDraw = false;
}

PlaneBSP::~PlaneBSP()
{
	if (plane != nullptr)
	{
		delete plane;
		plane = nullptr;
	}

	if (node != nullptr)
	{
		delete node;
		node = nullptr;
	}
}

void PlaneBSP::Init(Renderer* renderer, Entity* node, glm::vec3 position, glm::vec3 normal)
{
	plane = new Plane(normal, position);
	this->node = node;
}

void PlaneBSP::SwitchCanDrawStatus()
{
	node->visible = !node->visible;
}

bool PlaneBSP::SamePositionsSide(glm::vec3 point1, glm::vec3 point2)
{
	return plane->SameSide(point1, point2);
}