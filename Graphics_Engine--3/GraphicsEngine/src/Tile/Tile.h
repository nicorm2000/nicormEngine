#ifndef TILE_H
#define TILE_H
//============================================
#include "../Sprite/Sprite.h"
#include "../Exports/Exports.h"
//============================================
class Tile : public Sprite
{
public:
	GraficosEngine_API Tile();
	GraficosEngine_API Tile(Renderer* rend);
	GraficosEngine_API Tile(Renderer* rend, std::string path, bool flip);
	GraficosEngine_API ~Tile();

	GraficosEngine_API bool isWalkable();
	GraficosEngine_API void walkability(bool bWalkable);

	GraficosEngine_API uint getId();
	GraficosEngine_API void setId(uint id);

	GraficosEngine_API void setPosX(float x);
	GraficosEngine_API void setPosY(float y);

	void draw(Renderer* rend);
	void draw();



private:
	unsigned int _id;
	bool _walkable;
};
//============================================
#endif

