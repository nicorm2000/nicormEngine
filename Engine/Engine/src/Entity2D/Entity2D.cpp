#include "Entity2D.h"

Entity2D::Entity2D()
{
    material = new Material();
}

Entity2D::~Entity2D()
{
    if (material != nullptr)
    {
        material = nullptr;
        delete material;
    }
}