#include "Camera.h"
#include "../Renderer/Renderer.h"

void Camera::Init(Renderer* render, Window* window, float near, float far)
{
	_renderer = render;
	_window = window;
	BaseInit();
	_near = near;
	_far = far;
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
}
void Camera::BaseInit() {
	//--------
	transform.position = glm::vec3(0.0f);
	//--------
	transform.up = glm::vec3(0, 1, 0);
	transform.right = glm::vec3(0.0f);
	transform.forward = glm::vec3(0, 0, -1);
	//--------
	targetLook = glm::vec3(0.0f);
	WorldUp = glm::vec3(0.0f);
	//--------
	cameraType = CAMERA_TYPE::FPS;
	//--------
	Yaw = YAW;
	Pitch = PITCH;
	MovementSpeed = SPEED;
	_sensitivity = SENSITIVITY;
	_fov = ZOOM;
	_near = 0.1f;
	_far = 100.f;
	_offset = OFFSET;
}
void Camera::Init(Renderer* render, Window* window)
{
	_renderer = render;
	_window = window;
	BaseInit();
	SetAspect();
	//--------
	UpdateProjection();
	UpdateView();
	_renderer->SetUniform(_uniformViewPos, "viewPos");
}
void Camera::SetWindow(Window* window)
{
	_window = window;
}
void Camera::SetNear(float near)
{
	_near = near;
}
void Camera::SetAspect()
{
	float width = _window->GetWidth();
	float height = _window->GetHeight();
	SetAspect(width, height);
}
void Camera::SetAspect(float width, float height)
{
	_aspect = width / height;
}
Camera::Camera()
{
	_renderer = NULL;
	_ejes = false;
	transform.position = glm::vec3(0.0f);
	transform.up = glm::vec3(0.0f);
	transform.right = glm::vec3(0.0f);
	transform.forward = glm::vec3(0.0f);
	//--------
	targetLook = glm::vec3(0.0f);
	WorldUp = glm::vec3(0.0f);
	//--------
	cameraType = CAMERA_TYPE::FPS;
	//--------
	Yaw = 0;
	Pitch = 0;
	MovementSpeed = 0;
	_sensitivity = 0;
	_fov = 0;
	_aspect = 0;
	_near = 0;
	_far = 0;
	//--------
}
void Camera::SetViewMatrix(glm::vec3 startingPosition, glm::vec3 lookPosition, glm::vec3 upVector)
{
	targetLook = lookPosition;
	WorldUp = upVector;
	_renderer->SetView(glm::lookAt(startingPosition, lookPosition, upVector));
}
void Camera::SetTarget(Entity* target)
{
	_target = target;
}
Entity* Camera::GetTarget()
{
	return _target;
}
void Camera::SetSensitivity(float sensitivity)
{
	_sensitivity = sensitivity;
}
void Camera::SetOffset(float offset) {
	_offset = offset;
}
void Camera::Update()
{
	if (!_enabled)
		return;
	if (_target != NULL && cameraType == CAMERA_TYPE::TPS)
		transform.position = _target->getPos();
	UpdateCameraVectors();
	_renderer->UseShader();
	_renderer->UpdateVec3(_uniformViewPos, getPos());
}
void Camera::UpdateProjection()
{
	glm::mat4 projection = glm::perspective(glm::radians(_fov), _aspect, _near, _far);
	_renderer->SetProjection(projection);
}

void Camera::UpdateCameraVectors()
{
	if (!_ejes)
		return;
	// calculate the new Front vector
	glm::vec3 direction;
	direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	direction.y = sin(glm::radians(Pitch));
	direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	transform.forward = glm::normalize(direction);
	transform.right = glm::cross(transform.forward, transform.up);
	if (_target != NULL && cameraType == CAMERA_TYPE::TPS)
	{
		transform.position = _target->getPos() - transform.forward * _offset;
	}
	UpdateView();
}

void Camera::UpdateView()
{
	switch (cameraType)
	{
	case CAMERA_TYPE::FPS:
		SetViewMatrix(transform.position, transform.position + transform.forward, transform.up);
		return;
	case CAMERA_TYPE::TPS:
		if (_target != NULL)
			SetViewMatrix(transform.position, _target->getPos(), transform.up);
		return;
	case CAMERA_TYPE::FC:
		SetViewMatrix(transform.position, transform.position + transform.forward, transform.up);
		break;
	default:
		break;
	}

}
void Camera::ProcessMouseScroll(float yoffset)
{
	_fov -= (float)yoffset;
	if (_fov < 1.0f)
		_fov = 1.0f;
	if (_fov > 45.0f)
		_fov = 45.0f;
	UpdateProjection();
	if (_target != NULL && cameraType == CAMERA_TYPE::TPS)
		SetViewMatrix(transform.position, _target->getPos(), transform.up);

}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= _sensitivity;
	yoffset *= _sensitivity;


	Yaw += xoffset;
	Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	//std::cout << "x: " << xoffset << " y: " <<yoffset<<std::endl;
	// update Front, Right and Up Vectors using the updated Euler angles
	UpdateCameraVectors();
}


Camera::~Camera()
{

}

void Camera::SetCameraType(CAMERA_TYPE type)
{
	cameraType = type;
}

CAMERA_TYPE Camera::GetCameraType()
{
	return cameraType;
}

glm::vec3 Camera::GetFront()
{
	return transform.forward;
}
glm::vec3 Camera::GetRight()
{
	return transform.right;
}
glm::vec3 Camera::GetUp()
{
	return transform.up;
}
void Camera::ToogleEjes()
{
	_ejes = !_ejes;
	std::cout << "Camera update set (" << _ejes << ")" << std::endl;
}