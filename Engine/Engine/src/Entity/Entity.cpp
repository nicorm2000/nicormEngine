#include "Entity.h"
#include <chrono>
#include <thread>

float getFrameTime()
{
	static auto previousTime = std::chrono::high_resolution_clock::now();
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - previousTime).count();
	previousTime = currentTime;

	// Calculate frame time based on target frame rate
	constexpr float targetFrameRate = 60.0f;
	constexpr float targetFrameTime = 1.0f / targetFrameRate;

	// Delay if frame finished faster than target frame time
	if (duration < targetFrameTime)
	{
		std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameTime - duration));
		duration = targetFrameTime;
	}

	return duration;
}

Entity::Entity()
{
	model = glm::mat4(1.0f);

	translateMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);

	translateVector = glm::vec3(1.0f);
	rotateVector = glm::vec3(1.0f);
	scaleVector = glm::vec3(1.0f);

	VBO = 0;
	VAO = 0;
	EBO = 0;

	renderer = nullptr;
}

Entity::~Entity()
{
	if (renderer != nullptr)
	{
		renderer = nullptr;
		delete renderer;
	}
}

void Entity::UpdateModelMatrix()
{
	model = glm::mat4(1.0f);
	model = translateMatrix * rotateMatrix * scaleMatrix;
}

glm::mat4 Entity::GetModelMatrix()
{
	return model;
}

void Entity::SetPosition(float x, float y, float z)
{
	translateVector = glm::vec3(x, y, z); //Va a modificar la mat
	translateMatrix[3].x += x;
	translateMatrix[3].y += y;
	translateMatrix[3].z += z;

	UpdateModelMatrix();
}

void Entity::SetRotation(float x, float y, float z)
{
	rotateVector = glm::vec3(x, y, z);
	translateMatrix = glm::rotate(translateMatrix, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	
	UpdateModelMatrix();
}

void Entity::SetRotationX(float x)
{
	rotateVector = glm::vec3(x, 0, 0);
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
	UpdateModelMatrix();
}

void Entity::SetRotationY(float y)
{
	rotateVector = glm::vec3(0, y, 0);
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
	UpdateModelMatrix();
}

void Entity::SetRotationZ(float z)
{
	rotateVector = glm::vec3(0, 0, z);
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(z), glm::vec3(0.0, 0.0, 1.0));
	UpdateModelMatrix();
}

void Entity::SetScale(float x, float y, float z)
{
	scaleVector = glm::vec3(x, y, z); //Va a modificar la mat
	scaleMatrix[0].x = x;
	scaleMatrix[1].y = y;
	scaleMatrix[2].z = z;
	UpdateModelMatrix();
}

glm::vec3 Entity::GetPosition()
{
	return translateVector;
}

glm::vec3 Entity::GetRotation()
{
	return rotateVector;
}

glm::vec3 Entity::GetScale()
{
	return scaleVector;
}

void Entity::Translate(float x, float y, float z)
{
	translateMatrix = glm::translate(translateMatrix, glm::vec3(x, y, z));
	translateVector = glm::vec3(translateMatrix[3].x, translateMatrix[3].y, translateMatrix[3].z);
	UpdateModelMatrix();
}

void Entity::Rotate(float x, float y, float z)
{
	rotateMatrix = glm::rotate(rotateMatrix, x, glm::vec3(1, 0, 0));
	rotateMatrix = glm::rotate(rotateMatrix, y, glm::vec3(0, 1, 0));
	rotateMatrix = glm::rotate(rotateMatrix, z, glm::vec3(0, 0, 1));
	UpdateModelMatrix();
}

void Entity::Scale(float x, float y, float z)
{
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(x, y, z));
	scaleVector = glm::vec3(scaleMatrix[0].x, scaleMatrix[1].y, scaleMatrix[2].z);
	UpdateModelMatrix();
}