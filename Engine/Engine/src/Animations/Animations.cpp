#include "Animations.h"
#include "Timer/Timer.h"

Frame::Frame()
{
	uvCoords[0] = { 0.f, 0.f };
	uvCoords[1] = { 1.f, 0.f };
	uvCoords[2] = { 1.f, 1.f };
	uvCoords[3] = { 0.f, 1.f };
}

Frame::~Frame()
{
}

UVCords* Frame::GetUVCoords()
{
	return uvCoords;
}

Animation::Animation()
{

}

Animation::~Animation()
{

}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInMilisecs)
{
	animationDuration = durationInMilisecs;
	currentTime = 0;
	currentFrame = 0;
	Frame frame;

	frame.GetUVCoords()[0].U = frameX / textureWidth;
	frame.GetUVCoords()[0].V = frameY / textureHeight;

	frame.GetUVCoords()[1].U = (frameX + frameWidth) / textureWidth;
	frame.GetUVCoords()[1].V = frameY / textureHeight;

	frame.GetUVCoords()[2].U = frameX / textureWidth;
	frame.GetUVCoords()[2].V = (frameY + frameHeight) / textureHeight;

	frame.GetUVCoords()[3].U = (frameX + frameWidth) / textureWidth;
	frame.GetUVCoords()[3].V = (frameY + frameHeight) / textureHeight;

	frames.push_back(frame);
}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, int textureWidth, int textureHeight, float durationInMilisecs, int frameCount)
{
	animationDuration = durationInMilisecs;
	currentTime = 0;
	currentFrame = 0;
	int xCurrentFrame = 0;

	for (int i = 0; i < frameCount; i++)
	{
		Frame frame;

		frame.GetUVCoords()[0].U = (frameX + xCurrentFrame) / textureWidth;
		frame.GetUVCoords()[0].V = frameY / textureHeight;

		frame.GetUVCoords()[1].U = (frameX + frameWidth + xCurrentFrame) / textureWidth;
		frame.GetUVCoords()[1].V = frameY / textureHeight;

		frame.GetUVCoords()[2].U = (frameX + xCurrentFrame) / textureWidth;
		frame.GetUVCoords()[2].V = (frameY + frameHeight) / textureHeight;

		frame.GetUVCoords()[3].U = (frameX + frameWidth + xCurrentFrame) / textureWidth;
		frame.GetUVCoords()[3].V = (frameY + frameHeight) / textureHeight;

		frames.push_back(frame);
		xCurrentFrame += frameWidth;
	}
}

void Animation::Update()
{
	currentTime += Timer::GetDeltaTime() * 1000;

	while (currentTime > animationDuration)
	{
		currentTime -= animationDuration;
	}

	float frameLength = animationDuration / frames.size();
	currentFrame = static_cast<int>(currentTime / frameLength);
}

int Animation::GetCurrentFrame()
{
	return currentFrame;
}

std::vector<Frame> Animation::GetFrames()
{
	return frames;
}