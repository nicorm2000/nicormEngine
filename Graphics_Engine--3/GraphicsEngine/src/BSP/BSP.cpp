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
			DrawOnlyEntity(*it2);
		}
	}

	void BSP::DrawOnlyEntity(Entity2* e)
	{
		if (e->getMeshes().size() > 0)
			e->draw();
		if (e->getChildren().size() > 0)
		{
			for (int i = 0; i < e->getChildren().size(); i++)
			{
				DrawOnlyEntity(e->getChildren()[i]);
			}
		}
	}

	bool BSP::AskBox(plane* plan, Entity2* entity)
	{
		for (int i = 0; i < entity->getExtremos().size(); i++)
			if ((plan->GetSide(camera->getPos()) == plan->GetSide(entity->getExtremos()[i])))
				return true;
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
}