#ifndef ENTITY2D_H
#define ENTITY2D_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Entity/Entity.h"
#include "Material/Material.h"
#include "Export.h"

class DllApi Entity2D : public Entity
{
protected:
	Material* material;

	bool hasCollider;
	bool moveable;

public:
	Entity2D();
	~Entity2D();

	virtual void AttachMaterial() = 0;
	virtual void DetachMaterial() = 0;

	void SetCollider(bool hasCollider);
	void SetMoveable(bool moveable);
	bool IsMoveable();
	bool HasCollider();
};

#endif