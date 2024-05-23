#include "BSP.h"

bool BSP::enabled = true;
Renderer* BSP::renderer = nullptr;
Camera* BSP::camera = nullptr;

list<Entity*> BSP::entities = list<Entity*>();
list<PlaneBSP*> BSP::planes = list<PlaneBSP*>();

BSP::BSP()
{
	enabled = true;
	renderer = nullptr;
	camera = nullptr;

	entities = list<Entity*>();
	planes = list<PlaneBSP*>();
}

BSP::~BSP()
{
}

void BSP::Init(Renderer* render, Camera* cam)
{
	renderer = render;
	camera = cam;
}

void BSP::Update()
{
	//if (!enabled) return;

	UpdatePlanes();

	for (list<Entity*>::iterator itE = entities.begin(); itE != entities.end(); ++itE)
	{
		UpdateNodeVolume((*itE));
	}
}

void BSP::DeInit()
{
	entities.clear();
	planes.clear();
}

void BSP::FindPlanes(Entity* scene)
{
	list<Entity*> nodes = scene->GetNodes();

	if (!nodes.empty())
	{
		for (list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity* node = (*it);
			if (node->name.find("BSP") != string::npos)
			{
				AddPlane(node);
			}
			FindPlanes(node);
		}
	}
}

void BSP::AddPlane(Entity* node)
{
	PlaneBSP* plane = new PlaneBSP();
	plane->Init(renderer, node, node->vertex.Position, node->vertex.Normal);
	planes.push_back(plane);
}

void BSP::AddEntity(Entity* entity)
{
	entities.push_back(entity);
}

void BSP::UpdateNodeVolume(Entity* node)
{
	if (node->isOnFrustum)
	{
		bool drawEntity = true;

		if (enabled)
		{
			for (list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
			{
				Plane* plane = (*itP)->plane;

				if (node->GetGlobalVolume()->IsOnPlane(*plane) != plane->GetSide(camera->GetPosition()))
				{
					drawEntity = false;
					break;
				}
			}
		}

		node->visible = drawEntity;
		list<Entity*> nodes = node->GetNodes();

		if (!nodes.empty())
		{
			for (list<Entity*>::iterator itN = nodes.begin(); itN != nodes.end(); ++itN)
			{
				UpdateNodeVolume((*itN));
			}
		}
	}
}

void BSP::UpdatePlanes()
{
	for (list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
	{
		Plane* plane = (*itP)->plane;

		if (!plane->GetSide(camera->GetPosition()))
		{
			plane->Flip();
		}
	}
}

void BSP::TogglePlaneStatus()
{
	for (list<PlaneBSP*>::iterator it = planes.begin(); it != planes.end(); ++it)
	{
		(*it)->SwitchCanDrawStatus();
	}
}

void BSP::ToggleStatus()
{
	enabled = !enabled;
}