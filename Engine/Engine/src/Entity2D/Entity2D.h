#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity/Entity.h"

class Entity2D : public Entity
{
protected:
	Material* material;
public:
	Entity2D();
	~Entity2D();

	virtual void AttachMaterial() = 0;
	virtual void DetachMaterial() = 0;
};

#endif