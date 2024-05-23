#ifndef ENTITY_H
#define ENTITY_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include <list>
#include <vector>
#include <math.h>
#include "Renderer/Renderer.h"
#include "Volume/Volume.h"
#include "Volume/VolumeAABB.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "GLM/gtx/norm.hpp"
#include "Transform.h"
#include "Matrix.h"
#include "Vertexs.h"
using namespace std;

class DllApi Entity
{
protected:
	Renderer* renderer;

	Entity* parent;
	list<Entity*> nodes;

	VolumeAABB* localVolume;
	VolumeAABB* globalVolume;
	bool volumeDirty;
	bool drawVolume;

	unsigned int uniformModel;
	unsigned int uniformView;
	unsigned int uniformProjection;
	unsigned int locationPosition;
	unsigned int locationNormal;
	unsigned int locationTexCoord;

	bool IsCanDraw();
	void UpdateGlobalVolume();

	virtual void SetUniforms();
	virtual void UpdateShader();

private:
	glm::quat EulerToQuat(glm::vec3 euler);
	glm::vec3 QuatToVec(glm::quat quat, glm::vec3 euler);
	glm::quat GetRotationByMatrix(glm::mat4 mat);
	glm::vec3 ToEulerRad(glm::quat rot);
	glm::vec3 NormalizeAngles(glm::vec3 angles);
	float NormalizeAngle(float angle);

	void UpdateMatrix();
	void UpdateTransform();

	void UpdateNodesPos();
	void UpdateNodesRot();
	void UpdateNodesScale();

public:
	Entity();
	Entity(Renderer* renderer);
	~Entity();

	virtual void Update();
	virtual void Draw();
	virtual void DeInit();

	void SetParent(Entity* parent);
	void AddNode(Entity* node);
	void RemoveNode(Entity* node);
	void RemoveNode(string nodeName);
	void RemoveNode(int nodeIndex);

	void SetPosition(glm::vec3 position);
	void SetRotation(glm::vec3 rotation);
	void SetScale(glm::vec3 scale);

	void SetPosition(float x, float y, float z); 
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

	void SetRotation(float x, float y, float z);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);

	void SetScale(float x, float y, float z);
	void SetScale(float size);
	void SetMatrix(glm::mat4 mat);

	void LookTarget(glm::vec3 target);
	void SetDirection(glm::vec3 dir);

	Entity* GetParent();
	list<Entity*> GetNodes();
	Entity* GetNode(string nodeName);
	Entity* GetNode(int nodeIndex);

	Volume* GetGlobalVolume();
	void ToggleDrawVolume();
	void DrawVolume();

	glm::vec3 GetForward();
	glm::vec3 GetUp();
	glm::vec3 GetRight();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();

	glm::vec3 GetPosition(glm::mat4 mat);
	glm::vec3 GetRotation(glm::mat4 mat);
	glm::vec3 GetScale(glm::mat4 mat);

	glm::vec3 GetLocalPosition();
	glm::vec3 GetLocalRotation();
	glm::vec3 GetLocalScale();

	float GetPositionX();
	float GetPositionY();
	float GetPositionZ();

	float GetRotationX();
	float GetRotationY();
	float GetRotationZ();

	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();

	void Reset();

	Matrix matrix;
	Transform transform;

	Vertex vertex;

	string name;
	bool enabled;
	bool visible;
	bool isOnFrustum;
};

#endif