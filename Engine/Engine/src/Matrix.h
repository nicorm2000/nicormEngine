#ifndef MATRIX_H
#define MATRIX_H

#include "glm/glm.hpp"

struct Matrix
{
	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotation;
	glm::mat4 scale;
};

#endif