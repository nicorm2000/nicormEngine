#ifndef SHAPE_H
#define SHAPE_H

#include "Entity2D/Entity2D.h"

class DllApi Shape : public Entity2D
{
private:
	int TRIANGLE_POSITIONS_ARRAY_COUNT = 18;
	int TRIANGLE_INDEX_ARRAY_COUNT = 3;
	int SQUARE_POSITIONS_ARRAY_COUNT = 24;
	int SQUARE_INDEX_ARRAY_COUNT = 6;

	const int VERTEX_SIZE = 6;

	glm::vec3 colorVector;
public:
	Shape(Render* newRenderer);
	~Shape();

	void SetColor(glm::vec3 color);
	glm::vec3 GetColor();

	void AttachMaterial();
	void DetachMaterial();

	void CreateSquare();
	void CreateTriangle();

	void Draw();
};

#endif