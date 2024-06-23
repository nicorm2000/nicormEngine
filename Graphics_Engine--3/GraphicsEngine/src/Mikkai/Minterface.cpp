#include "Minterface.h"
using namespace glm;
namespace color
{
	struct RGB colorConverter(int hexValue)
	{
		struct RGB rgbColor;
		rgbColor.r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
		rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
		rgbColor.b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte

		return rgbColor;
	}
	vec4 colorConverter(vec4 a)
	{
		if (a.r > 1 || a.g > 1 || a.b > 1)
			a /= 255.0;
		return a;
	}
	vec3 colorConverter(vec3 a)
	{
		if (a.r > 1 || a.g > 1 || a.b > 1)
			a /= 255.0;
		return a;
	}
}