#ifndef TILE_H
#define TILE_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Sprite/Sprite.h"
using namespace std;

class DllApi Tile : public Sprite
{
private:
	unsigned int id;
	bool isWalkeable;

public:
	Tile();
	Tile(Renderer* render);
	~Tile();

	unsigned int GetId();
	void SetId(unsigned int id);

	bool IsWalkeable();
	void SetWalkeable(bool walkeable);

	void SetRender(Renderer* renderer);
};

#endif