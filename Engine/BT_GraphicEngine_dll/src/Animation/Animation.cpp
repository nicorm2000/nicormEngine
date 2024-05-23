#include "Animation.h"

// ------------------------------------------- FRAME -------------------------------------------
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

UVCoords* Frame::GetUVCords()
{
	return uvCoords;
}
// ----------------------------------------- ANIMATION -----------------------------------------

Animation::Animation()
{
	currentTime = 0.0f;
	currentFrame = 0;
	speed = 1.0f;
	textureData = nullptr;
	frames = std::vector<Frame>();
}

Animation::~Animation()
{
	frames.clear();
}

bool Animation::Update()
{
	currentTime += Timer::GetDeltaTime() * speed;

	if (currentTime > 1.0f)
	{
		currentTime = 0;
		currentFrame++;
		if (currentFrame == frames.size())
		{
			currentFrame = 0;
		}
		return true;
	}

	return false;
}

void Animation::SetAnimation(Texture* textureData, float speed)
{
	this->textureData = textureData;
	this->speed = speed;
}

void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, int frameCount)
{
	float frameXIndex = 0;

	for (int i = 0; i < frameCount; i++)
	{
		Frame frame;

		frame.GetUVCords()[0].U = (frameWidth * (frameX + 1)) / textureData->width;
		frame.GetUVCords()[0].V = (frameHeight / textureData->height) * frameY;

		frame.GetUVCords()[1].U = (frameWidth * (frameX + 1)) / textureData->width;
		frame.GetUVCords()[1].V = (frameHeight / textureData->height) * (frameY - 1);

		frame.GetUVCords()[2].U = (frameWidth * frameX) / textureData->width;
		frame.GetUVCords()[2].V = (frameHeight / textureData->height) * (frameY - 1);

		frame.GetUVCords()[3].U = (frameWidth * frameX) / textureData->width;
		frame.GetUVCords()[3].V = (frameHeight / textureData->height) * frameY;

		frames.push_back(frame);
		frameXIndex += frameWidth;
	}
}

void Animation::AddFrames(AtlasConfig atlas)
{
	if (atlas.useSize)
	{
		atlas.width = (int)(textureData->width / atlas.cols);
		atlas.height = (int)(textureData->height / atlas.rows);
	}

	int framesCount = 0;
	int x = atlas.offsetX;

	for (int i = atlas.offsetY; i < atlas.rows; i++)
	{
		while (x < atlas.cols)
		{
			Frame frame;
			frame.GetUVCords()[0].U = (atlas.width + (atlas.width * x)) / textureData->width;			// top right
			frame.GetUVCords()[0].V = (atlas.height * i) / textureData->height;						    // top right
			frame.GetUVCords()[1].U = (atlas.width + (atlas.width * x)) / textureData->width; 		    // bottom right
			frame.GetUVCords()[1].V = (atlas.height + (atlas.height * i)) / textureData->height;		// bottom right
			frame.GetUVCords()[2].U = (atlas.width * x) / textureData->width;							// bottom left
			frame.GetUVCords()[2].V = (atlas.height + (atlas.height * i)) / textureData->height;		// bottom left
			frame.GetUVCords()[3].U = (atlas.width * x) / textureData->width;							// top left 
			frame.GetUVCords()[3].V = (atlas.height * i) / textureData->height;						    // top left 

			frames.push_back(frame);
			framesCount++;
			x++;
			if (framesCount == atlas.frameCount) return;
		}

		x = 0;
	}
}

int Animation::GetCurrentFrame()
{
	return currentFrame;
}

std::vector<Frame> Animation::GetFrames()
{
	return frames;
}