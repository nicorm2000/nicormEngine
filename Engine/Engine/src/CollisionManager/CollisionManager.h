#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Entity2D/Entity2D.h"
#include "Export.h"

class DllApi CollisionManager
{
private:
	Entity2D* entity2D;

	const float collisionMoveSpeed = 0.001f;

public:
	CollisionManager();
	~CollisionManager();

	static void CollisionUpdate(Entity2D* entity1, Entity2D* entity2);
	static bool CheckCollision(Entity2D* entity1, Entity2D* entity2);
	static void Overlap(Entity2D* entity1, Entity2D* entity2);
};

#endif