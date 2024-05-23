#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <glew.h>
#include <glfw3.h>
#include <math.h>
#include "Export.h"
#include "Entity2D/Entity2d.h"
using namespace std;

class DllApi CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static void CollisionUpdate(Entity2D* entity1, Entity2D* entity2);
	static bool CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2);
	static void Overlap(Entity2D* entity1, Entity2D* entity2);
};

#endif