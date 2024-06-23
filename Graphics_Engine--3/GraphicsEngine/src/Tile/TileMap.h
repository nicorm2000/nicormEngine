//#ifndef TILEMAP_H
//#define TILEMAP_H
////================================================
//#include <string>
//#include "../Exports/Exports.h"
//#include "tinyxml2.h"
//#include <iostream>
//#include "Tile.h"
//#include "../Collision/Collision.h"
////================================================
//class TileMap {
//public:
//
//	GraficosEngine_API TileMap();
//	GraficosEngine_API TileMap(Renderer* rend);
//	GraficosEngine_API ~TileMap();
//
//	GraficosEngine_API const Tile& tile(unsigned int uiId);
//	GraficosEngine_API void setTile(const Tile& rkTile);
//	GraficosEngine_API void setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId);
//
//	GraficosEngine_API void setDimensions(float width, float heigth);
//	GraficosEngine_API void setTileDimensions(float tileWidth, float tileHeigth);
//
//	//GraficosEngine_API void setTexture(const Texture& rkTexture);
//	//GraficosEngine_API void setTexture(std::string filePathImage, bool flip);
//	GraficosEngine_API void setSize(float size);
//
//	GraficosEngine_API void draw();
//
//	GraficosEngine_API void draw(int layer);
//
//	GraficosEngine_API bool importTileMap(std::string filePath, std::string imagepath);
//
//	GraficosEngine_API bool checkCollision(Entity2D& object);
//
//	GraficosEngine_API void draw2(int layer);
//
//private:
//	std::vector<Tile> tiles;
//	std::vector<Tile**> _tileMapGrid;
//
//	unsigned int _width;
//	unsigned int _height;
//
//	float _tileWidth;
//	float _tileHeight;
//
//	Texture* _texture;
//
//	float _imageWidth;
//	float _imageHeight;
//
//	float convertedPosX;
//	float convertedPosY;
//
//	std::string _imagePath;
//
//	Renderer* _render;
//};
//#endif