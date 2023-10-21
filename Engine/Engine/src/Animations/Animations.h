#ifndef ANIMATION_H
#define ANIMATION_H

struct UVCords
{
	float U;
	float V;
};

#include <iostream>
#include "Export.h"
#include <vector>

class DllApi Frame
{
public:
	Frame();
	~Frame();
	UVCords* GetUVCoords();

private:
	UVCords uvCoords[4];
};

class DllApi Animation
{
private:
	int currentFrame;
	float currentTime;
	float speed;
	float length;
	std::vector<Frame> frames;

public:
	Animation();
	~Animation();

	void Update();
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInSecs);
	void AddFrame(float frameX, float frameY, int rows, int cols, int widthTexture, int heightTexture);
	void SetSpeed(float newSpeed);
	int GetCurrentFrame();
	std::vector<Frame> GetFrames();
};

#endif   
