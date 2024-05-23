#ifndef CAMERA_H
#define CAMERA_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Entity/Entity.h"
using namespace std;

class DllApi Camera : public Entity
{
protected:
	void SetUniforms() override;
	void UpdateShader() override;

	void UpdateDirection();
	void UpdateView();
	void UpdateProjection();

	glm::mat4 view;
	glm::mat4 projection;

	unsigned int uniformViewPosition;

	float yaw;
	float pitch;

	float fov;
	float aspect;
	float near;
	float far;

	float sensitivity;

	Entity* target;
	float offset;
	bool followTarget;

public:
	Camera(Renderer* renderer);
	~Camera();

	void Init(float fov, float width, float height, float near, float far);
	void Update();	
	void Rotate();
	void Reset();

	void SetFOV(float fov);
	void SetYaw(float yaw);
	void SetPitch(float pitch);
	void SetSensitivity(float sensitivity);
	void SetTarget(Entity* target);
	void SetOffset(float offset);
	void SetFollowStatus(bool status);

	float GetFOV();
	float GetYaw();
	float GetPitch();
	float GetSensitivity();

	float GetNear();
	float GetFar();
	float GetAspect();
};

#endif