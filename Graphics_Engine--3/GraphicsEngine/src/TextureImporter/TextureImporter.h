#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include "../Exports/Exports.h"
#include "Texture2/Texture2.h"
#include <string>


typedef unsigned int uint;
class GraficosEngine_API TextureImporter {
	struct TextureData
	{
		unsigned int id;
		int width;
		int height;
		int channel;
	};

public:
	static bool LoadTexture(const std::string& path, uint& texture, int& width, int& height, int& channels,bool flip);
	static MikkaiEngine::Texture LoadTexture(const char* path, bool invertImage);
};

#endif