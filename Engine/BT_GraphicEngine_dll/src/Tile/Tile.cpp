#include "Tile.h"

Tile::Tile()
{
	id = 0;
	isWalkeable = false;
}

Tile::Tile(Renderer* render) : Sprite(render)
{
	id = 0;
	isWalkeable = false;
}

Tile::~Tile()
{
}

unsigned int Tile::GetId()
{
	return id;
}

void Tile::SetId(unsigned int id)
{
	this->id = id;
}

bool Tile::IsWalkeable()
{
	return isWalkeable;
}

void Tile::SetWalkeable(bool walkeable)
{
	isWalkeable = walkeable;
}
void Tile::SetRender(Renderer* renderer)
{
	this->renderer = renderer;
}