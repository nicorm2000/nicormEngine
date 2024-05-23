#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include "Export.h"
#include "StbImage/Stb_image.h"
using namespace std;

enum class TEXTURE_TYPE
{
	BASE,
	DIFFUSE,
	SPECULAR
};

struct Texture
{
	unsigned int ID;
	float width;
	float height;
	string type;
	string path;
};

class DllApi TextureImporter
{
public:
	TextureImporter();
	~TextureImporter();

	static Texture LoadTexture(const char* path, bool invertImage);
};

#endif 