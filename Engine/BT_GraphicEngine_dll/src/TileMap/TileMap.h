#ifndef TILEMAP_H
#define TILEMAP_H

#include <glew.h>
#include <glfw3.h>
#include <vector>
#include "Export.h"
#include "Tile/Tile.h"
#include "Tinyxml2/tinyxml2.h"
#include "CollisionManager/CollisionManager.h"
#include "TextureImporter/TextureImporter.h"
using namespace std;

class DllApi Tilemap
{
private:
	Renderer* renderer;

	vector<Tile> tiles;
	vector<Tile**> grid;

	unsigned int width;
	unsigned int height;

	float tileWidth;
	float tileHeight;

	Texture texture;

	float imageWidth;
	float imageHeight;

public:
	Tilemap();
	Tilemap(Renderer* renderer);
	~Tilemap();

	void SetTile(Tile tile);
	void SetMapTileId(int layer, unsigned int col, unsigned int row, unsigned int id);
	void SetDimentions(float width, float height);
	void SetTileDimentions(float tileWidth, float tileHeight);
	void SetSize(float size);

	const Tile& GetTile(unsigned int id);

	bool ImportTileMap(string filePath, string imagePath);
	void CheckCollision(Entity2D* entity);

	void Draw();
	void DeInit();
};

#endif