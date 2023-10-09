#include "TextureImporter.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture TextureImporter::LoadTexture(std::string path, bool invertImage)
{
	unsigned int textureId;
	int textureWidth;
	int textureHeight;
	int nrChannels;

	glGenTextures(1, &textureId); // Se genera la textura
	glBindTexture(GL_TEXTURE_2D, textureId); // Se bindea (se marca como es la textura con la que se va a trabajar)

	// Se establecen las opciones de ajuste/filtrado de la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // En el caso de que se haga mas chiquita la textura, se dice como debería filtrarse
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Carga y genera la textura
	stbi_set_flip_vertically_on_load(invertImage); // Esto es porque OpenGL espera las texturas al reves
	unsigned char* data = stbi_load(path.c_str(), &textureWidth, &textureHeight, &nrChannels, 0);

	if (data)
	{
		int channelType = GL_RGBA;
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

	Texture tex = { textureId, textureWidth, textureHeight };
	return tex;
}