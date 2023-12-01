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
	float animationDuration;
	float currentTime;
	int currentFrame;
	std::vector<Frame> frames;

public:
	Animation();
	~Animation();

	void Update();
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInMilisecs);
	void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, int textureWidth, int textureHeight, float durationInMilisecs, int frameCount);
	int GetCurrentFrame();
	std::vector<Frame> GetFrames();
};

#endif   
