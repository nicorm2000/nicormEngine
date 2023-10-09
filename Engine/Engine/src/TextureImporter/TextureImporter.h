#ifndef TEXTUREIMPORTER_H
#define TEXTUREIMPORTER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Export.h"

struct Texture
{
	unsigned int ID;
	float width;
	float height;
};

static class DllApi TextureImporter
{
private:

public:
	static Texture LoadTexture(std::string path, bool invertImage);
};

#endif 