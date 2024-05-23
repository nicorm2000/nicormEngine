#include "Color.h"

const float colorValue = 255.f;

Color::Color()
{
	R = 1.f;
	G = 1.f;
	B = 1.f;
	A = 1.f;
}

Color::Color(float R, float G, float B, float A)
{
	this->R = R;
	this->G = G;
	this->B = B;
	this->A = A;
}

Color::Color(int R, int G, int B, int A)
{
	SetColorRGBA(R, G, B, A);
}

Color::~Color()
{
}

void Color::SetColorRGB(int R, int G, int B)
{
	this->R = glm::clamp(static_cast<float>(R), 0.f, colorValue) / colorValue;
	this->G = glm::clamp(static_cast<float>(G), 0.f, colorValue) / colorValue;
	this->B = glm::clamp(static_cast<float>(B), 0.f, colorValue) / colorValue;
}

void Color::SetColorRGBA(int R, int G, int B, int A)
{
	SetColorRGB(R, G, B);
	this->A = glm::clamp(static_cast<float>(A), 0.f, colorValue) / colorValue;
}

glm::vec3 Color::GetColorRGB()
{
	return glm::vec3(R, G, B);
}

glm::vec4 Color::GetColorRGBA()
{
	return glm::vec4(R, G, B, A);
}

Color Color::GetRandomColor()
{
	int R = rand() % (static_cast<int>(colorValue) + 1);
	int G = rand() % (static_cast<int>(colorValue) + 1);
	int B = rand() % (static_cast<int>(colorValue) + 1);
	int A = rand() % (static_cast<int>(colorValue) + 1);

	return Color(R, G, B, A);
}