#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Renderer/Render.h"
#include "Export.h"

class DllApi Entity
{
protected:
	Render* renderer;

	//Entity* parent;
	//list<Entity*> nodes;
	//
	//VolumeAABB* localVolume;
	//VolumeAABB* globalVolume;
	//bool volumeDirty;
	//bool drawVolume;

	unsigned int uniformModel;
	unsigned int uniformView;
	unsigned int uniformProjection;
	unsigned int locationPosition;
	unsigned int locationNormal;
	unsigned int locationTexCoord;

	//bool IsCanDraw();
	//void UpdateGlobalVolume();

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

	virtual void SetUniforms();
	virtual void UpdateShader();

private:
	//glm::quat EulerToQuat(glm::vec3 euler);
	//glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
	//glm::quat GetRotationByMatrix(glm::mat4 mat);
	//glm::vec3 ToEulerRad(glm::quat rot);
	//glm::vec3 NormalizeAngles(glm::vec3 angles);
	//float NormalizeAngle(float angle);
	//
	//void UpdateMatrix();
	//void UpdateTransform();
	//
	//void UpdateNodesPos();
	//void UpdateNodesRot();
	//void UpdateNodesScale();

public:
	Entity();
	Entity(Render* renderer);
	~Entity();

	void UpdateModelMatrix();
	glm::mat4 GetModelMatrix();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetScale(float x, float y, float z);

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	void Translate(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void Scale(float x, float y, float z);

	virtual void Draw();
};