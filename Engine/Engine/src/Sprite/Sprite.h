#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/Entity2D.h"
#include "Animations/Animations.h"
#include "TextureImporter/TextureImporter.h"
#include "Export.h"

class DllApi Sprite : public Entity2D
{
private:
	int POSITIONS_ARRAY_COUNT = 32;
	int INDEX_ARRAY_COUNT = 6;
	int VERTEX_SIZE = 8;

	glm::vec3 colorVector;

	Animation* animation;
	Texture texture;
public:
	Sprite();
	Sprite(Render* newRenderer, std::string path);
	~Sprite();

	int heightTexture;
	int widthTexture;

	void AttachMaterial();
	void DetachMaterial();
	void Draw();

	void CreateAnimation(float speed);
	void AddFrames(int rows, int cols);
	void AddFrame(float frameX, float frameY, int rows, int cols);
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight);
	void SetUVCoords(Frame frame);
	void SetTextureCoords(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);
	void UpdateAnimation();
	void UpdateAnimation(Animation* animation);

	void LoadTexture(std::string path, bool invertImage);

	void SetColor(glm::vec3);
	glm::vec3 GetColor();
};

#endif