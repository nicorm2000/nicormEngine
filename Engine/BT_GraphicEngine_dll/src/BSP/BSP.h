#ifndef BSP_H
#define BSP_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Entity/entity.h"
#include <PlaneBSP/planeBSP.h>
#include <Camera/camera.h>
#include <list>
using namespace std;

class DllApi BSP
{
private:
	static bool enabled;
	static Renderer* renderer;
	static Camera* camera;

	static list<Entity*> entities;
	static list<PlaneBSP*> planes;

public:
	BSP();
	~BSP();

	static void Init(Renderer* render, Camera* cam);
	static void Update();
	static void DeInit();

	static void FindPlanes(Entity* scene);
	static void AddPlane(Entity* node);

	static void AddEntity(Entity* entity);

	static void UpdateNodeVolume(Entity* node);
	static void UpdatePlanes();

	static void TogglePlaneStatus();
	static void ToggleStatus();
};

#endif