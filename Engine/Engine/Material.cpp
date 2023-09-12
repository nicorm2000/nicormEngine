#include "Material.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

Material::Material()
{
}

Material::~Material()
{
}

ShaderProgramSource Material::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;

	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}

	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Material::CompilerShader(unsigned int type, const std::string& source)
{
	ID = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(ID, 1, &src, nullptr);
	glCompileShader(ID);

	int result;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length);

		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(ID, length, &length, message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(ID);
		return 0;
	}

	return ID;
}

void Material::CreateMaterial(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = NULL;
	program = glCreateProgram();
	unsigned int vs = CompilerShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompilerShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs); // Atachea los dos shaders al programa
	glAttachShader(program, fs);
	glLinkProgram(program); // Lo linkea
	glValidateProgram(program); // Valida que este todo bien

	ID = program;
}

void Material::UseMaterial()
{
	glUseProgram(ID);
}

void Material::DeleteMaterial()
{
	glDeleteProgram(ID);
}