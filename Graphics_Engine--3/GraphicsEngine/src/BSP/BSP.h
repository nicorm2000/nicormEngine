#ifndef BSP_H
#define BSP_H

#include "Entity2/Entity2.h"
#include "Camera2/Camera2.h"
#include "Plan/Plane.h"
#include <list>

namespace MikkaiEngine
{
	class GraficosEngine_API BSP
	{
	public:
		BSP();
		BSP(Renderer* render, Camera2* camera);
		~BSP() {};

		void Init() {};
		void Update() {};
		void Draw();
		bool AskBox(plane* plan, Entity2* entity);
		void DeInit();

		void AddEntity(Entity2* entity);
		void AddPlane(glm::vec3 position, glm::vec3 normal);
		void AddPlane(plane* plan);
		void AddPlane(Entity2* plan);
		void TogglePlaneStatus();

	private:
		Renderer* render;
		Camera2* camera;

		std::list<Entity2*> entities;
		std::list<plane*> planes;
	};
}

#endif