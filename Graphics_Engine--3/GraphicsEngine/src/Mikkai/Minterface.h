#ifndef MINTERFACE_H
#define MINTERFACE_H
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "../Exports/Exports.h"
#include <string>
using namespace glm;
namespace  color
{
	GraficosEngine_API typedef struct RGB
	{
		float r;
		float g;
		float b;
		RGB(float r, float g, float b)
		{
			if (r>1||g>1||b>1)
			{
				this->r = r / 255.0f;
				this->g = g / 255.0f;
				this->b = b / 255.0f;
				
				return;
			}
			if (r<0 || g<0 || b<0)
			{
				this->r = 1;
				this->g = 1;
				this->b = 1;
				return;
			}
			this->r = r;
			this->g = g;
			this->b = b;
		}
		RGB(std::string hexValue) {
			const char* str = hexValue.c_str();
			int r, g, b;
			sscanf_s(str, "%02x%02x%02x", &r, &g, &b);
			this->r = r / 255.0;  // Extract the RR byte
			this->g = g / 255.0;   // Extract the GG byte
			this->b = b / 255.0;   // Extract the BB byte
		}
		RGB() 
		{
			r = 1;
			g = 1;
			b = 1;
		};
	};

	GraficosEngine_API struct RGB colorConverter(int hexValue);
	GraficosEngine_API vec4 colorConverter(vec4 a);
	GraficosEngine_API vec3 colorConverter(vec3 a);
	 


	GraficosEngine_API typedef struct RGBA
	{
		RGB _RGB;
		float _A;
		GraficosEngine_API vec4 GetColorV4() 
		{
			return glm::vec4(_RGB.r, _RGB.g, _RGB.b, _A);
		}
		GraficosEngine_API vec3 GetColorV3()
		{
			return glm::vec3(_RGB.r, _RGB.g, _RGB.b);
		}
		void SetColor(float r, float g, float b, float a)
		{
			_RGB = RGB(r, g, b);
			_A = a;
		}
		void SetColor(float r, float g, float b)
		{
			_RGB = RGB(r, g, b);
			_A = 1.0f;
		}
		void SetColor(glm::vec3 a)
		{
			_RGB = RGB(a.r, a.g, a.b);
			_A = 1.0f;
		}
		RGBA()
		{
			_RGB = RGB(1, 1, 1);
			_A = 1.0f;
		}
		RGBA(RGB rgb)
		{
			_RGB = rgb;
			_A= 1.0f;
		}
		RGBA(glm::vec4 v)
		{
			_RGB.r = v.r;
			_RGB.g = v.g;
			_RGB.b = v.b;
			_A = v.a;
		}
	};


	
}
GraficosEngine_API typedef struct VecToString
{
	static std::string vec3toString(glm::vec3 value) {
		std::string res;
		res = std::to_string(value.x) +","+ std::to_string(value.y) +"," + std::to_string(value.z);
		return res;
	}
	static glm::vec3 StringtoVec3(std::string value) {
		glm::vec3 res = vec3(0,0,0);
		const char* finder = value.c_str();
		float multiplicador=1;
		float counter=0;
		//------obtener valor en x.
		while (*finder!=',')
		{
			counter++;
			finder++;
			if (counter>1)
				multiplicador *= 10;
		}
		for (int i = 0; i < counter; i++)
		{
			res.x += value.c_str()[i]-48;
			multiplicador /= 10;
		}
		multiplicador = 1;
		//-----------obtener valor en y.
		finder++;
		while (*finder != ',')
		{
			counter++;
			finder++;
			if (counter > 1)
				multiplicador *= 10;
		}
		for (int i = 0; i < counter; i++)
		{
			res.y += value.c_str()[i] - 48;
			multiplicador /= 10;
		}
		multiplicador = 1;
		//-----------obtener valor en z.
		finder++;
		while (*finder != ',')
		{
			counter++;
			finder++;
			if (counter > 1)
				multiplicador *= 10;
		}
		for (int i = 0; i < counter; i++)
		{
			res.z += value.c_str()[i] - 48;
			multiplicador /= 10;
		}
		multiplicador = 1;
		//-----------Devolver.
		return res;
	}
};


GraficosEngine_API typedef struct VecUtils {
#include <cmath>
	static float magnitude(vec3 v)
	{
		return (sqrtf(powf(v.x,2)+ powf(v.y,2)+ powf(v.z,2)));
	}
};
#endif
