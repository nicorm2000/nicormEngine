#ifndef ANIMATION_H
#define ANIMATION_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Timer/Timer.h"
#include "TextureImporter/TextureImporter.h"
#include "AtlasConfig.h"
#include <vector>
using namespace std;

// ------------------------------------------- FRAME -------------------------------------------
struct UVCoords
{
	float U, V;
};

class DllApi Frame
{
private:
	UVCoords uvCoords[4];

public:
	Frame();
	~Frame();
	UVCoords* GetUVCords();
};
// ------------------------------------------- FRAME -------------------------------------------

class DllApi Animation
{
private:
	float currentTime;
	int currentFrame;
	float speed;
	Texture* textureData;
	vector<Frame> frames;

public:
	Animation();
	~Animation();

	bool Update();
	void SetAnimation(Texture* textureData, float speed);
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, int frameCount);
	void AddFrames(AtlasConfig atlas);
	int GetCurrentFrame();
	vector<Frame> GetFrames();
};

#endif