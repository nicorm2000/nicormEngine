#include "TextureImporter.h"

#include <iostream>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include <ctype.h>

#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#define STBI_WINDOWS_UTF8

/*https://learnopengl.com/Getting-started/Textures*/
static bool NameContainsOnlyASCII(std::string textureName) {
	bool containsOnlyASCII = true;
	for (auto c : textureName)
		if (!isascii(c))
			containsOnlyASCII = false;

	return containsOnlyASCII;
}

bool TextureImporter::LoadTexture(const std::string& path, uint& texture, int& width, int& height, int& channels,bool flip) {
	unsigned char* data;
	stbi_set_flip_vertically_on_load(flip);

	std::string pathName = path;
	data = stbi_load(pathName.c_str(), &width, &height, &channels, 0);

	if (!data) 
	{
		std::cout << "Cant read the data texture" << std::endl;
		return false;
	}
		
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/*Cada una de las opciones antes mencionadas se puede establecer por eje de coordenadas 
	( s, t(y rsi está utilizando 3D texturas) equivalentes a x, y, z)
	con elglTexParameter* función:*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	/*GL_NEAREST da como resultado patrones bloqueados donde podemos ver claramente los píxeles que forman la textura,
	mientras que GL_LINEAR produce un patrón más suave donde los píxeles individuales son menos visibles.
	GL_LINEAR produce una salida más realista, pero algunos desarrolladores prefieren un aspecto más de 8 bits y,
	como resultado, eligen la opción GL_NEAREST .
	El filtrado de texturas se puede configurar para aumentador y minificandooperaciones
	(al escalar hacia arriba o hacia abajo) para que pueda, por ejemplo,
	usar el filtrado de vecino más cercano cuando las texturas se escalan hacia abajo y el filtrado lineal para texturas a mayor escala.
	Por lo tanto, tenemos que especificar el método de filtrado para ambas opciones a través deglTexParameter*.
	El código debería verse similar a la configuración del método de envoltura:*/

	//seria diferente forma de visualizar.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (channels == 4) //dependiendo de los canales, va a usar para rgba o rgb, sino se rompe todo.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	else if (channels == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (channels == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	else if (channels == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//Esto generará automáticamente todos los mapas MIP necesarios para la textura enlazada actualmente.
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
	std::cout << " W: "<<width<< " H: "<<height<< " Ch: "<< channels << std::endl;
	return true;
}
MikkaiEngine::Texture TextureImporter::LoadTexture(const char* path, bool invertImage)
{
	unsigned int textureId;
	int textureWidth;
	int textureHeight;
	int nrChannels;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	stbi_set_flip_vertically_on_load(invertImage);
	unsigned char* data = stbi_load(path, &textureWidth, &textureHeight, &nrChannels, 0);
	if (data)
	{
		int channelType = GL_RGB;
		switch (nrChannels)
		{
		case 1:
			channelType = GL_R;
			break;
		case 2:
			channelType = GL_RG;
			break;
		case 3:
			channelType = GL_RGB;
			break;
		case 4:
			channelType = GL_RGBA;
			break;
		default:
			break;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, channelType, textureWidth, textureHeight, 0, channelType, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	return MikkaiEngine::Texture{ textureId, (float)textureWidth, (float)textureHeight, "", "" };
}



	

	
