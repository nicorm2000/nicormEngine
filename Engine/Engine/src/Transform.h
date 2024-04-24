#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct Transform
{
	glm::vec3 position;
	glm::vec3 eulerAngles;
	glm::vec3 scale;
	glm::quat rotation;

	glm::vec3 localPosition;
	glm::vec3 localEulerAngles;
	glm::vec3 localScale;
	glm::quat localRotation;

	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;
};

#endif