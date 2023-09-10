#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"
#include <string>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class DllApi Material
{
private:
	unsigned int ID = -1;

public:
	Material();
	~Material();

	ShaderProgramSource ParseShader(const std::string& filePath);
	unsigned int CompilerShader(unsigned int type, const std::string& source);
	void CreateMaterial(const std::string& vertexShader, const std::string& fragmentShader);
	void UseMaterial();
	void DeleteMaterial();
};

#endif