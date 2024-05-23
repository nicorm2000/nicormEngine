#ifndef COLOR_H
#define COLOR_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "glm/ext/matrix_transform.hpp"
using namespace std;

class DllApi Color
{
private:
	float R, G, B, A;

public:
	Color();
	Color(float R, float G, float B, float A);
	Color(int R, int G, int B, int A);
	~Color();

	void SetColorRGB(int R, int G, int B);
	void SetColorRGBA(int R, int G, int B, int A);

	glm::vec3 GetColorRGB();
	glm::vec4 GetColorRGBA();

	static Color GetRandomColor();
};

#endif=