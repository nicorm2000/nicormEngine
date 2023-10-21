#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
    material = new Material();

    hasCollider = false;
    moveable = false;
}

Entity2D::~Entity2D()
{
    if (material != nullptr)
    {
        material = nullptr;
        delete material;
    }
}

void Entity2D::SetCollider(bool hasCollider)
{
    this->hasCollider = hasCollider;
}

void Entity2D::SetMoveable(bool moveable)
{
    this->moveable = moveable;
}

bool Entity2D::IsMoveable()
{
    return moveable;
}

bool Entity2D::HasCollider()
{
    return hasCollider;
}