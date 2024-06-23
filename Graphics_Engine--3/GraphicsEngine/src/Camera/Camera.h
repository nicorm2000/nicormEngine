#ifndef CAMERA_H
#define CAMERA_H
#include "Exports/Exports.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Entity/Entity.h"

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;
const float OFFSET		= 10.f;
class Renderer;

enum class CAMERA_TYPE
{
	FC,
	FPS,
	TPS,
	Max
};

class GraficosEngine_API Camera : public Entity
{
public:
	//--------Builder Destroy Init----------
	Camera();
	~Camera();
	void Init(Renderer* render, Window* window);
	void Init(Renderer* render, Window* window, float near, float far);
	void SetWindow(Window* window);
	//--------Seters----------
	void SetNear(float);
	void SetAspect();
	void SetAspect(float width, float height);
	void SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector);
	void SetTarget(Entity* target);
	void SetSensitivity(float sensitivity);
	void SetOffset(float offset);
	void SetCameraType(CAMERA_TYPE type);
	//------------------------
	//------Updates-----------
	void Update();
	void UpdateProjection();

	void UpdateCameraVectors();
	void UpdateView();
	void ProcessMouseScroll(float yoffset);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
	void ToogleEjes();
	//--------Getters-------
	Entity* GetTarget();
	CAMERA_TYPE GetCameraType();
	glm::vec3 GetFront();
	glm::vec3 GetRight();
	glm::vec3 GetUp();
	//--------Others--------
	void DebugInfo();
	bool _ejes;
	bool _mouseMoveCamera;
private:
	friend class MyImGui;

	void BaseInit();

	Entity* _target;
	Window* _window;

	uint _uniformViewPos;
	
	glm::vec3 targetLook;
	glm::vec3 WorldUp;
	

	CAMERA_TYPE cameraType;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float _sensitivity;
	float _fov;
	float _aspect;
	float _near;
	float _far;
	float _offset;


};
#endif