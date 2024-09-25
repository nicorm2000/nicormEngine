#include "bsp.h"

namespace MikkaiEngine
{
	BSP::BSP()
	{
		render = nullptr;
		camera = nullptr;

		entities = std::list<Entity2*>();
		planes = std::list<plane*>();
	}

	BSP::BSP(Renderer* render, Camera2* camera)
	{
		this->render = render;
		this->camera = camera;

		entities = std::list<Entity2*>();
		planes = std::list<plane*>();
	}

	void BSP::Draw()
	{
		for (std::list<Entity2*>::iterator it2 = entities.begin(); it2 != entities.end(); ++it2)
		{
			DrawRecursive(*it2);
		}
	}

	void BSP::DrawOnlyEntity(Entity2* e)
	{
		for (std::list<plane*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			bool dibujar = true;
			if (!AskBox((*it), e)) // pregunto si la camara y si uno de los puntos esta en la misma cara del plano
			{
				dibujar = false;
				break;
			}
			if (dibujar)
			{
				DrawRecursive(e);
			}
		}
	}

	void BSP::DrawRecursive(Entity2* e)
	{
		for (int i = 0; i < e->getChildren().size(); i++)
		{
			DrawRecursive(e->getChildren()[i]);
		}
		e->SetcanDrawThisFrame(true);
		for (std::list<plane*>::iterator it = planes.begin(); it != planes.end(); ++it)
		{
			if (!AskBox((*it), e))
			{
				e->SetcanDrawThisFrame(false);
				break;
			}
		}
		if ((e)->canDrawThisFrame())
			if (e->getMeshes().size() > 0)
				e->draw();
	}

	bool BSP::AskBox(plane* plan, Entity2* entity)
	{
		for (int i = 0; i < entity->getExtremos().size(); i++)
		{
			bool A = plan->GetSide(camera->getPos());

			bool B = plan->GetSide(entity->getExtremos()[i]);

			if (A == B)
				return true;
		}
		return false;
	}

	void BSP::DeInit()
	{
		entities.clear();

		planes.clear();
	}

	void BSP::AddEntity(Entity2* entity)
	{
		entities.push_back(entity);
	}

	void BSP::AddPlane(glm::vec3 position, glm::vec3 normal)
	{
		plane* plan = new plane(normal, position);

		planes.push_back(plan);
	}

	void BSP::AddPlane(plane* plan)
	{
		planes.push_back(plan);
	}

	void BSP::AddPlane(Entity2* entity)
	{
		if (entity->getName().find("bsp") != std::string::npos)
		{
			glm::vec3 forward = normalize(entity->GetUp());
			plane* plan = new MikkaiEngine::plane(forward, entity->getPos());
			planes.push_back(plan);
		}
	}

	void BSP::TogglePlaneStatus()
	{
		//for (std::list<plane*>::iterator it = planes.begin(); it != planes.end(); ++it)
		//{
		//	(*it)->SwitchCanDrawStatus();
		//}
	}

	//void BSP::UpdateNodeVolume(Entity2* node)
	//{
	//	bool drawEntity = true;
	//
	//	for (std::list<PlaneBSP*>::iterator itP = planes.begin(); itP != planes.end(); ++itP)
	//	{
	//		if (node->GetGlobalVolume()->IsOnPlane(*(*itP)->plane) != (*itP)->plane->GetSide(camera->GetPos()))
	//		{
	//			drawEntity = false;
	//			break;
	//		}
	//	}
	//	node->visible = drawEntity;
	//
	//	std::list<Entity*> nodes = node->GetNodes();
	//	if (!nodes.empty())
	//	{
	//		for (std::list<Entity*>::iterator itN = nodes.begin(); itN != nodes.end(); ++itN)
	//		{
	//			UpdateNodeVolume((*itN));
	//		}
	//	}
	//}
}