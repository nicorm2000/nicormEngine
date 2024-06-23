//#include "TileMap.h"
//
//
////================================================
//TileMap::TileMap(){}
//TileMap::TileMap(Renderer* rend) {_render = rend;}
////================================================
//TileMap::~TileMap() {}
////================================================
//const Tile& TileMap::tile(unsigned int uiId) {
//	Tile* NoTile = nullptr;
//
//	for (int i = 0; i < tiles.size(); i++) {
//		if (uiId == tiles[i].getId()) {
//			return tiles[i];
//		}
//	}
//
//	return *NoTile;
//}
////================================================
//void TileMap::setMapTileId(int layer, unsigned int uiCol, unsigned int uiRow, unsigned int uiId) {
//	_tileMapGrid[layer][uiCol][uiRow] = tile(uiId);
//}
////================================================
//void TileMap::setTile(const Tile& rkTile) {
//	tiles.push_back(rkTile);
//}
////================================================
//void TileMap::setTileDimensions(float tileWidth, float tileHeight) {
//	_tileWidth = tileWidth;
//	_tileHeight = tileHeight;
//}
////================================================
//void TileMap::setDimensions(float width, float height) {
//	_width = width;
//	_height = height;
//
//	//creo la grilla bidimensional para guardar la posicion de cada tile igual que en el editor
//	Tile** tileMap;
//	tileMap = new Tile * [_height];
//	for (int i = 0; i < _height; i++) {
//		tileMap[i] = new Tile[_width];
//	}
//	_tileMapGrid.push_back(tileMap);
//}
////================================================
////void TileMap::setTexture(const Texture& rkTexture) {
////	_texture = rkTexture;
////}
////void TileMap::setTexture(std::string filePathImage, bool flip) {
////	_texture.LoadTexture(filePathImage, flip);
////}
////================================================
//void TileMap::draw() {
//
//	float mapWidth = -(_width * _tileWidth) / 2;
//	float mapHeight = (_height * _tileHeight) / 2;
//
//	for (int i = 0; i < _tileMapGrid.size(); i++) {
//		for (int y = 0; y < _height; y++) {
//			for (int x = 0; x < _width; x++) {
//				if (_tileMapGrid[i][y][x].getId() != NULL) {
//					_tileMapGrid[i][y][x].setPosX(mapWidth + (_tileWidth * x));
//					_tileMapGrid[i][y][x].setPosY(mapHeight - (_tileHeight * y));
//					_tileMapGrid[i][y][x].draw();
//				}
//			}
//		}
//	}
//
//}
//void TileMap::draw(int layer) {
//
//	float mapWidth = -(_width * _tileWidth) / 2;
//	float mapHeight = (_height * _tileHeight) / 2;
//
//	for (int y = 0; y < _height; y++) {
//		for (int x = 0; x < _width; x++) {
//			if (_tileMapGrid[layer][y][x].getId() != NULL) {
//				_tileMapGrid[layer][y][x].setPosX(mapWidth + (_tileWidth * x));
//				_tileMapGrid[layer][y][x].setPosY(mapHeight - (_tileHeight * y));
//				_tileMapGrid[layer][y][x].draw();
//			}
//		}
//	}	
//}
//void TileMap::draw2(int layer) {
//	for (int y = 0; y < _height; y++) {
//		for (int x = 0; x < _width; x++) {
//			if (_tileMapGrid[layer][y][x].getId() != NULL) {
//				_tileMapGrid[layer][y][x].draw();
//			}
//		}
//	}
//}
////================================================
////On Test, Dont work yet.
//void TileMap::setSize(float size)
//{
//	float mapWidth = -((_width * size) * (_tileWidth*size)) / 2;
//	float mapHeight = ((_height * size) * (_tileHeight*size)) / 2;
//
//	for (int i = 0; i < _tileMapGrid.size(); i++) {
//		for (int y = 0; y < _height; y++) {
//			for (int x = 0; x < _width; x++) {
//				if (_tileMapGrid[i][y][x].getId() != NULL) {
//					_tileMapGrid[i][y][x].setPosX((mapWidth + (_tileWidth * x))*size);
//					_tileMapGrid[i][y][x].setPosY((mapHeight - (_tileHeight * y))*size);
//					_tileMapGrid[i][y][x].SetScale(_tileWidth * size, _tileHeight * size);
//				}
//			}
//		}
//	}
//}
//bool TileMap::importTileMap(std::string filePath,std::string imagepath) {
//	tinyxml2::XMLDocument doc; //guarda el documento
//	tinyxml2::XMLError errorHandler; //guarda el resultado de las funciones
//
//	errorHandler = doc.LoadFile(filePath.c_str()); //carga el archivo XML
//	if (errorHandler == tinyxml2::XML_ERROR_FILE_NOT_FOUND || errorHandler == tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED) return false;
//
//	// Loading Map element and save Map width, heigth in tiles and width, heigth of Tiles in pixels
//	tinyxml2::XMLElement* mapNode = doc.FirstChildElement("map");
//	if (mapNode == nullptr)
//		return false;
//	setDimensions(mapNode->FloatAttribute("width"), mapNode->FloatAttribute("height"));				// Get width and heigth for
//	setTileDimensions(mapNode->FloatAttribute("tilewidth"), mapNode->FloatAttribute("tileheight")); // the map and the tiles
//
//	// Loading Tilset element
//	//tinyxml2::XMLElement* pTileset = mapNode->FirstChildElement("tileset");
//	tinyxml2::XMLElement* pTileset = mapNode->LastChildElement("tileset");
//	if (pTileset == NULL)
//		return false;
//
//	int tileCount = pTileset->IntAttribute("tilecount"); // Number of Tiles in the Tileset
//	int columns = pTileset->IntAttribute("columns");  // Columns of Tiles in the Tileset
//	int rows = tileCount / columns;
//
//	//std::string _imagePath = "../../Game/res";																//
//	//pTileset->FirstChildElement("image")->Attribute("source");			// Loading Textures
//	//setTexture(_imagePath.c_str(),true);
//	//setTexture(LoadTexture(_imagePath.c_str(), D3DCOLOR_XRGB(255, 255, 255))); //
//	_texture = new Texture(imagepath, false);
//	// Save the Tiles in the TileMap
//	_imageWidth = pTileset->FirstChildElement("image")->IntAttribute("width");
//	_imageHeight = pTileset->FirstChildElement("image")->IntAttribute("height");
//	float tileX = 0.0f, tileY = 0.0f;
//	int _id = 1;
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < columns; j++) {
//			Tile newTile;
//
//			newTile.setId(_id);
//			newTile.SetTexture(_texture);
//			newTile.SetScale(_tileWidth, _tileHeight);
//
//			newTile.Init(SPRITE_TYPE::CUBE);
//
//			//newTile.setTextureCoordinates((tileX + _tileWidth) / _imageWidth, tileY / _imageHeight, // top right
//			//	(tileX + _tileWidth) / _imageWidth, (tileY + _tileHeight) / _imageHeight,// bottom right
//			//	tileX / _imageWidth, (tileY + _tileHeight) / _imageHeight,// bottom left
//			//	tileX / _imageWidth, tileY / _imageHeight);// top left tileX / imageWidth, tileY / imageHeight
//
//			tileX += _tileWidth;
//			setTile(newTile);
//			_id++;
//		}
//		tileX = 0;
//		tileY += _tileHeight;
//	}
//
//	tinyxml2::XMLElement* pTile = pTileset->FirstChildElement("tile");
//
//	while (pTile) {
//		unsigned int id = pTile->IntAttribute("id");
//		tinyxml2::XMLElement* pProperty = pTile->FirstChildElement("properties")->FirstChildElement("property");
//		std::string propertyName = pProperty->Attribute("value");
//		if (propertyName == "false")
//		{
//			tiles[id].walkability(false);
//			tiles[id]._hasCollider = true;
//		}
//		else
//		{
//			tiles[id].walkability(true);
//			tiles[id]._hasCollider = true;
//		}
//
//		pTile = pTile->NextSiblingElement("tile");
//	}
//
//	// Loading Layer element
//	tinyxml2::XMLElement* pLayer = mapNode->FirstChildElement("layer");
//	if (pLayer == NULL)
//		return false;
//
//	int layerCount = 0;
//	while (pLayer) {
//		// Loading Data element
//		tinyxml2::XMLElement* pData = pLayer->FirstChildElement("data");
//		if (pData == NULL)
//			return false;
//
//		if (layerCount > 0) {
//			Tile** tileMap;
//			tileMap = new Tile * [_height];
//			for (int i = 0; i < _height; i++) {
//				tileMap[i] = new Tile[_width];
//			}
//			_tileMapGrid.push_back(tileMap);
//		}
//
//		while (pData) {
//			std::vector<int> tileGids;
//			for (tinyxml2::XMLElement* pTile = pData->FirstChildElement("tile");
//				pTile != NULL;
//				pTile = pTile->NextSiblingElement("tile"))
//			{
//				unsigned int gid = std::atoi(pTile->Attribute("gid")); // tile's id is saved
//				tileGids.push_back(gid);
//			}
//
//			int gid = 0;
//			for (int y = 0; y < _height; y++) {
//				for (int x = 0; x < _width; x++) {
//					if (tileGids[gid] != 0)
//						setMapTileId(layerCount, y, x, tileGids[gid]);
//					gid++;
//				}
//			}
//
//			pData = pData->NextSiblingElement("data");
//		}
//		layerCount++;
//		pLayer = pLayer->NextSiblingElement("layer");
//	}
//
//	return true;
//}
////================================================
//bool TileMap::checkCollision(Entity2D& object) {
//
//	convertedPosX = object.getPos().x + (_width / 2) * _tileWidth;
//	convertedPosY = object.getPos().y - (_height / 2) * _tileHeight;
//
//	int left_tile = convertedPosX / _tileWidth;
//	int right_tile = (convertedPosX + object.getScale().x) / _tileWidth;
//
//	int top_tile = (convertedPosY / _tileHeight) * -1;
//	int bottom_tile = ((convertedPosY - object.getScale().y) / _tileHeight) * -1; // Se resta porque el eje Y crece hacia arriba
//
//	if (left_tile < 0)
//		left_tile = 0;
//
//	if (right_tile >= _width)
//		right_tile = _width - 1;
//
//	if (top_tile < 0)
//		top_tile = 0;
//
//	if (bottom_tile >= _height)
//		bottom_tile = _height - 1;
//
//	for (int i = left_tile; i <= right_tile; i++) {
//
//		for (int j = top_tile; j <= bottom_tile; j++) {
//
//			for (int k = 0; k < _tileMapGrid.size(); k++) {
//				if (!_tileMapGrid[k][j][i].isWalkable()) {
//
//					if (Collision::CheckCollisionRecRecTile(&object, &_tileMapGrid[k][j][i]))
//					{
//						std::cout << "collision:  " << std::endl;
//						Collision::GoLastPos(&_tileMapGrid[k][j][i], &object);
//					}
//
//					return true;
//				}
//			}
//		}
//	}
//	return false;
//}