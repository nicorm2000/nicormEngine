#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Export.h"

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
	//void ModifyMaterial(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::mat4 modelMatrix, glm::vec3 colorVector, unsigned int texture = 0);
	void DeleteMaterial();
};

#endif