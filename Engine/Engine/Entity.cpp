#include "Entity.h"

Entity::Entity()
{
	VBO = 0;
	translateVector.x = 0.0f;
	translateVector.y = 0.0f;
	translateVector.z = 0.0f;

	rotateVector.x = 0.0f;
	rotateVector.y = 0.0f;
	rotateVector.z = 0.0f;

	scaleVector.x = 1.0f;
	scaleVector.y = 1.0f;
	scaleVector.z = 1.0f;
}

Entity::~Entity()
{

}

void Entity::SetPosition(float x, float y, float z)
{
	translateVector.x = x;
	translateVector.y = y;
	translateVector.z = z;
}

void Entity::SetRotation(float x, float y, float z)
{
	rotateVector.x = x;
	rotateVector.y = y;
	rotateVector.z = z;
}

void Entity::SetScale(float x, float y, float z)
{
	scaleVector.x = x;
	scaleVector.y = y;
	scaleVector.z = z;
}

void Entity::Translate(float x, float y, float z)
{

}

void Entity::Rotate(float x, float y, float z)
{

}

void Entity::Scale(float x, float y, float z)
{

}

Vec3 Entity::GetPosition()
{
	return translateVector;
}

Vec3 Entity::GetRotation()
{
	return rotateVector;
}

Vec3 Entity::GetScale()
{
	return scaleVector;
}
