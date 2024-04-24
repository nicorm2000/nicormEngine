#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class DllApi Shader
{
private:
	unsigned int shaderId;

	void VertexShader(string vertexPath);
	void FragmentShader(string fragmentPath);
	void LinkShader();
	string ReadShaderFile(string path);

public:
	Shader();
	~Shader();

	void CreateShader(string vertexPath, string fragmentPath);
	unsigned int GetShaderId();
};

#endif