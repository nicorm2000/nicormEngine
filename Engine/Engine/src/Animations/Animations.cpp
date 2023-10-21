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
	currentTime = 0;
	currentFrame = 0;
	length = 1000;
	frames = std::vector<Frame>();
	speed = 1.0f;
}

Animation::~Animation()
{
	frames.clear();
}

void Animation::Update()
{
	currentTime += Timer::GetDeltaTime() * speed;

	while (currentTime > length)
	{
		currentTime -= length;
	}

	float frameLength = length / frames.size();
	currentFrame = static_cast<int>(currentTime / frameLength);
}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float durationInSecs)
{
	length = durationInSecs;

	Frame frame;

	frame.GetUVCoords()[0].U = (frameX * frameWidth) / textureWidth;
	frame.GetUVCoords()[0].V = (frameY * frameHeight) / textureHeight;

	frame.GetUVCoords()[1].U = ((frameX + 1) * frameWidth) / textureWidth;
	frame.GetUVCoords()[1].V = (frameY * frameHeight) / textureHeight;

	frame.GetUVCoords()[2].U = (frameX * frameWidth) / textureWidth;
	frame.GetUVCoords()[2].V = ((frameY + 1) * frameHeight) / textureHeight;

	frame.GetUVCoords()[3].U = ((frameX + 1) * frameWidth) / textureWidth;
	frame.GetUVCoords()[3].V = ((frameY + 1) * frameHeight) / textureHeight;

	frames.push_back(frame);
}

void Animation::AddFrame(float frameX, float frameY, int rows, int cols, int widthTexture, int heightTexture)
{
	AddFrame(frameX, frameY, widthTexture / cols, heightTexture / rows, widthTexture, heightTexture, 1);
}

void Animation::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

int Animation::GetCurrentFrame()
{
	return currentFrame;
}

std::vector<Frame> Animation::GetFrames()
{
	return frames;
}