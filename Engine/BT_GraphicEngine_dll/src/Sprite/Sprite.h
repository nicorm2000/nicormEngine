#ifndef SPRITE_H
#define SPRITE_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Entity2D/Entity2D.h"
#include "Animation/Animation.h"
#include "TextureImporter/TextureImporter.h"
#include "Material/TextureMaterial.h"
#include "StbImage/stb_image.h"
using namespace std;

enum class SPRITE_TYPE
{
	QUAD,
	CUBE
};

class DllApi Sprite : public Entity2D
{
private:
	SPRITE_TYPE spriteType;
	unsigned int UVB;

	Texture* baseTexture;
	unsigned int uniformBaseTexture;

	int animationIndex = 0;
	vector<Animation*> animation;
	Frame frame;

	bool transparent;

	void SetUniforms() override;
	void UpdateShader() override;

public:
	Sprite();
	Sprite(Renderer* renderer);
	~Sprite();

	void Init(SPRITE_TYPE spriteType);
	void Update();
	void Draw();
	void DeInit();

	void SetTexture(Texture* texture, TEXTURE_TYPE textureType);
	void LoadTexture(const char* path, bool invertImage, TEXTURE_TYPE textureType);
	void AddAnimation(AtlasConfig atlas, float speed);
	void AddAnimation(int rows, int cols, float duration);
	void ChangeAnimation(int index);
	void SetTextureCoordinates(Frame frame);

	void SetTransparent(bool transparent);
	bool GetTransparent();
};

#endif