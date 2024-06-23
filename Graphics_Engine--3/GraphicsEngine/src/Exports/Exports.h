#ifndef EXPORTS_H
#define EXPORTS_H
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

	#ifdef GraficosEngine_API
		#define GraficosEngine_API __declspec(dllexport) //Especifica clase para exportacion
	#else
		#define GraficosEngine_API __declspec(dllimport) //Especifica clase para importacion
	#endif
typedef unsigned int uint;

#endif