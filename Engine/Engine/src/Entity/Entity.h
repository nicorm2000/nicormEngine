#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Render.h"
#include "Export.h"

class DllApi Entity
{
protected:
	Render* renderer;

	unsigned int VAO; //Vertex Array Object
	unsigned int VBO; //Vertex Buffer Object
	unsigned int EBO; //Element Buffer Object

	glm::mat4 model;

	glm::mat4 translateMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;

	glm::vec3 translateVector;
	glm::vec3 rotateVector;
	glm::vec3 scaleVector;

public:
	Entity();
	~Entity();

	void UpdateModelMatrix();
	glm::mat4 GetModelMatrix();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	virtual void Draw() = 0;
};