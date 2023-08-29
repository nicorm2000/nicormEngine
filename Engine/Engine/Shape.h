#pragma once

#include "Vectors.h"
#include "Entity2D.h"

class Shape : public Entity2D
{
private:
	int TRIANGLE_POSITIONS_ARRAY_COUNT = 18;
	int TRIANGLE_INDEX_ARRAY_COUNT = 3;
	int SQUARE_POSITIONS_ARRAY_COUNT = 24;
	int SQUARE_INDEX_ARRAY_COUNT = 6;

	const int VERTEX_SIZE = 6;

	Vec3 colorVector;
public:
	Shape();
	~Shape();

	void SetColor(Vec3 color);
	Vec3 GetColor();

	void CreateSquare();
	void CreateTriangle();

	void Draw();
};