#include "animation.h"
#include <iostream>
#include "../Time/Time.h"


	//Animation::Animation()
	//{
	//	currentTime = 0;
	//	currentFrame = 0;
	//	length = 1000;
	//	frames = std::vector<Frame>();
	//	actions = std::vector<std::vector<Frame>>();
	//	actionLength = -1;
	//	lastAction = 0;
	//}
	//void Animation::SetAnimation(MyTexture* tex, float speed)
	//{
	//	this->texture = tex;
	//	this->speed = speed;
	//}
	//
	//Animation::~Animation()
	//{
	//	frames.clear();
	//}
	//
	//void Animation::Update(float timer)
	//{
	//	currentTime += timer;
	//	while (currentTime > length)
	//	{
	//		currentTime -= length;
	//	}
	//
	//	float frameLength = length / frames.size();
	//	currentFrame = static_cast<int>(currentTime / frameLength);
	//}
	//bool Animation::Update2(float timer)
	//{
	//	//correguir el tema del sangrado (si) y la speed (si).
	//	currentTime += timer * speed;
	//	if (currentTime > length)
	//	{
	//		currentTime -= length;
	//		currentFrame++;
	//		if (currentFrame == frames.size())
	//		{
	//			currentFrame = 0;
	//		}
	//		return true;
	//	}
	//	return false;
	//}
	//
	//void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float duration)
	//{
	//	std::cout << "Frame: Fx["<< frameX<<"] Fy["<<frameY<<"]--Create" << std::endl;
	//	length = duration;
	//	
	//		Frame frame;
	//
	//		frame.GetUVCords()[0].u = (frameWidth * (frameX - 1)) / textureWidth;
	//		frame.GetUVCords()[0].v = (frameHeight / textureHeight) * frameY;
	//
	//		frame.GetUVCords()[1].u = (frameWidth * (frameX - 1)) / textureWidth;
	//		frame.GetUVCords()[1].v = (frameHeight / textureHeight) * (frameY + 1);
	//
	//		frame.GetUVCords()[2].u = (frameWidth * frameX) / textureWidth;
	//		frame.GetUVCords()[2].v = (frameHeight / textureHeight) * (frameY + 1);
	//
	//		frame.GetUVCords()[3].u = (frameWidth * frameX) / textureWidth;
	//		frame.GetUVCords()[3].v = (frameHeight / textureHeight) * frameY;
	//
	//		frames.push_back(frame);
	//
	//}
	//void Animation::AddFrame2(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float duration)
	//{
	//	length = duration;
	//	float frameXIndex = 0;
	//
	//
	//	Frame frame;
	//
	//	frame.GetUVCords()[0].u = (frameWidth * (frameX + 1)) / textureWidth;
	//	frame.GetUVCords()[0].v = (frameHeight / textureHeight) * frameY;
	//
	//	frame.GetUVCords()[1].u = (frameWidth * (frameX + 1)) / textureWidth;
	//	frame.GetUVCords()[1].v = (frameHeight / textureHeight) * (frameY - 1);
	//
	//	frame.GetUVCords()[2].u = (frameWidth * frameX) / textureWidth;
	//	frame.GetUVCords()[2].v = (frameHeight / textureHeight) * (frameY - 1);
	//
	//	frame.GetUVCords()[3].u = (frameWidth * frameX) / textureWidth;
	//	frame.GetUVCords()[3].v = (frameHeight / textureHeight) * frameY;
	//
	//	frames.push_back(frame);
	//	frameXIndex += frameWidth;
	//}
	//void Animation::AddFrames(Atlas atlas)
	//{
	//	length = atlas.duration;
	//	if (atlas.useSize)
	//	{
	//		atlas.width = (int)(texture->_width / atlas.cols);
	//		atlas.height = (int)(texture->_height / atlas.rows);
	//	}
	//
	//	int framesCount = 0;
	//	int x = atlas.offsetX;
	//	for (int i = atlas.offsetY; i < atlas.rows; i++)
	//	{
	//		while (x < atlas.cols)
	//		{
	//			Frame frame;
	//			frame.GetUVCords()[0].u = (float)(atlas.width + (atlas.width * x)) / texture->_width;			// top right
	//			frame.GetUVCords()[0].v = (float)(atlas.height * i) / texture->_height;						// top right
	//			frame.GetUVCords()[1].u = (float)(atlas.width + (atlas.width * x)) / texture->_width; 		// bottom right
	//			frame.GetUVCords()[1].v = (float)(atlas.height + (atlas.height * i)) / texture->_height;		// bottom right
	//			frame.GetUVCords()[2].u = (float)(atlas.width * x) / texture->_width;							// bottom left
	//			frame.GetUVCords()[2].v = (float)(atlas.height + (atlas.height * i)) / texture->_height;		// bottom left
	//			frame.GetUVCords()[3].u = (float)(atlas.width * x) / texture->_width;							// top left 
	//			frame.GetUVCords()[3].v = (float)(atlas.height * i) / texture->_height;						// top left 
	//			frames.push_back(frame);
	//			framesCount++;
	//			x++;
	//			if (framesCount == atlas.frameCount) return;
	//		}
	//		x = 0;
	//	}
	//}
	//int Animation::GetCurrentFrame()
	//{
	//	return currentFrame;
	//}
	//
	//void Animation::SetCurrentFrame(int frame, float* vertex)
	//{
	//	//if (frame != 0)
	//	{
	//		Frame f = GetFrames()[frame];
	//
	//		float uvCoords[]
	//		{
	//			f.GetUVCords()[0].u, f.GetUVCords()[0].v,
	//			f.GetUVCords()[1].u, f.GetUVCords()[1].v,
	//			f.GetUVCords()[2].u, f.GetUVCords()[2].v,
	//			f.GetUVCords()[3].u, f.GetUVCords()[3].v
	//		};
	//		vertex[6] = uvCoords[0];
	//		vertex[14] = uvCoords[2];
	//		vertex[22] = uvCoords[4];
	//		vertex[30] = uvCoords[6];
	//
	//		vertex[7] = uvCoords[1];
	//		vertex[15] = uvCoords[3];
	//		vertex[23] = uvCoords[5];
	//		vertex[31] = uvCoords[7];
	//	}
	//}
	//
	//
	//int Animation::SetAnAction(int firstFrame, int LastFrame)
	//{
	//	std::vector<Frame> vf;
	//	for (int i = firstFrame; i <= LastFrame;  i++)
	//	{
	//		vf.push_back(GetFrames()[i]);
	//	}
	//	actions.push_back(vf);
	//	actionLength++;
	//	return actionLength;
	//}
	//
	//void Animation::UpdateAction(float time, int action)
	//{
	//	currentTime += time;
	//	while (currentTime > length)
	//	{
	//		currentTime -= length;
	//	}
	//	if (actionLength < action)
	//	return;
	//	float frameLength = length / actions[action].size();
	//	currentFrame = static_cast<int>(currentTime / frameLength);
	//	//currentFrame += action * actions[action].size();
	//	for (int i = 0; i < action; i++)
	//	{
	//		currentFrame += actions[i].size();
	//	}
	//}
	//
	//std::vector<Frame> Animation::GetFrames()
	//{
	//	return frames;
	//}
	//
	//Frame::Frame()
	//{
	//	uvcords[0] = { 1,1 };
	//	uvcords[1] = { 1,0 };
	//	uvcords[2] = { 0,0 };
	//	uvcords[3] = { 0,1 };
	//}
	//
	//Frame::~Frame()
	//{
	//}
	//
	//UVCords* Frame::GetUVCords()
	//{
	//	return uvcords;
	//}
