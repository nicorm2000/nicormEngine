#pragma once

#include "Vectors.h"

class Entity
{
private:
	unsigned int VBO; //Vertex Buffer Object
	Vec3 translateVector;
	Vec3 rotateVector;
	Vec3 scaleVector;

public:
	Entity();
	~Entity();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	Vec3 GetPosition();
	Vec3 GetRotation();
	Vec3 GetScale();

	virtual void Draw() = 0;
};