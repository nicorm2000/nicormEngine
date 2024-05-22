#include "Camera.h"

//Dep agregar la herencia de : Entity(renderer)
Camera::Camera(Render* renderer) : Entity(renderer)
{
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	uniformViewPosition = 0;

	yaw = -90.f;
	pitch = 0.f;

	fov = 0.0f;
	aspectRatio = 0.0f;
	near = 0.0f;
	far = 0.0f;

	sensitivity = 0.5f;

	target = nullptr;
	offset = 0.0f;	
	followTarget = false;
}

Camera::~Camera()
{
}

void Camera::Init(float fov, float width, float height, float near, float far)
{
	aspectRatio = width / height;
	this->fov = fov;
	this->near = near;
	this->far = far;

	//SetUniforms();
	UpdateProjection();
}

void Camera::Update()
{
	UpdateDirection();
	UpdateProjection();
	//UpdateShader();
}

void Camera::Rotate()
{
	if (pitch > 89.0f)pitch = 89.0f;
	if (pitch < -89.0f)pitch = -89.0f;

	UpdateDirection();
}

void Camera::Reset()
{
	SetPosition(0.0f, 0.0f, 0.0f);
	UpdateView();
}

void Camera::SetFOV(float fov)
{
	this->fov = fov;
	UpdateProjection();
}

void Camera::SetYaw(float yaw)
{
	this->yaw = yaw;
}

void Camera::SetPitch(float pitch)
{
	this->pitch = pitch;
}

void Camera::SetTarget(Entity* target)
{
	this->target = target;
}

void Camera::SetSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

void Camera::SetOffset(float offset)
{
	this->offset = offset;
}

void Camera::SetFollowStatus(bool status)
{
	followTarget = status;
}

float Camera::GetFOV()
{
	return fov;
}

float Camera::GetSensitivity()
{
	return sensitivity;
}
float Camera::GetYaw()
{
	return yaw;
}

float Camera::GetPitch()
{
	return pitch;
}

float Camera::GetNear()
{
	return near;
}

float Camera::GetFar()
{
	return far;
}

float Camera::GetAspectRatio()
{
	return aspectRatio;
}

void Camera::UpdateDirection()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//SetDirection(direction);

	//if (target != nullptr)
	//{
	//	if (followTarget) SetPosition(target->GetPosition() - transform.forward * offset);
	//	else SetPosition(target->GetPosition());
	//}

	UpdateView();
}

void Camera::UpdateView()
{
	//if (followTarget)
	//{
	//	view = glm::lookAt(transform.position, target->GetPosition(), transform.up);
	//}
	//else
	//{
	//	view = glm::lookAt(transform.position, transform.position + transform.forward, transform.up);
	//}

	renderer->SetView(view);
}

void Camera::UpdateProjection()
{
	projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
	renderer->SetProjection(projection);
}

void Camera::SetUniforms()
{
	//Dep
	//Entity::SetUniforms();
	//renderer->SetUniform(uniformViewPosition, "viewPosition");
}

void Camera::UpdateShader()
{
	//Dep
	//renderer->UseShader();
	//Entity::UpdateShader();
	//renderer->UpdateVec3(uniformViewPosition, transform.position);
	//renderer->CleanShader();
}