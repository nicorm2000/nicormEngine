#ifndef SHAPE_H
#define SHAPE_H

#include <glew.h>
#include <glfw3.h>
#include "Entity2D/Entity2D.h"
using namespace std;

enum class SHAPE_TYPE
{
	TRIANGLE,
	QUAD,
	CUBE
};

class DllApi Shape : public Entity2D
{
public:
	Shape();
	Shape(Renderer* renderer);
	~Shape();

	void Init(SHAPE_TYPE shapeType);
	void Draw();
	void DeInit();
};

#endif