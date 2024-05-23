#include "OcclusionCulling.h"

Camera* OcclusionCulling::camera = nullptr;

Plane OcclusionCulling::up = Plane();
Plane OcclusionCulling::down = Plane();
Plane OcclusionCulling::left = Plane();
Plane OcclusionCulling::right = Plane();
Plane OcclusionCulling::front = Plane();
Plane OcclusionCulling::back = Plane();

OcclusionCulling::OcclusionCulling()
{
	camera = nullptr;

	up = Plane();
	down = Plane();
	left = Plane();
	right = Plane();
	front = Plane();
	back = Plane();
}

OcclusionCulling::~OcclusionCulling()
{
}

void OcclusionCulling::Init(Camera* cam)
{
	camera = cam;
}

void OcclusionCulling::Update()
{
	float fov = camera->GetFOV();
	float aspect = camera->GetAspect();
	// float aspect = camera->GetAspect() / 2; --> For check oclussion culling work

	float halfHeight = camera->GetFar() * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
	float halfWidth = halfHeight * aspect;

	glm::vec3 frontFar = camera->GetFar() * camera->GetForward();

	back.SetPositionAndNormal(camera->GetPosition() + camera->GetNear() * camera->GetForward(), camera->GetForward());
	front.SetPositionAndNormal(camera->GetPosition() + frontFar, -camera->GetForward());
	right.SetPositionAndNormal(camera->GetPosition(), glm::cross(camera->GetUp(), frontFar + camera->GetRight() * halfWidth));
	left.SetPositionAndNormal(camera->GetPosition(), glm::cross(frontFar - camera->GetRight() * halfWidth, camera->GetUp()));
	up.SetPositionAndNormal(camera->GetPosition(), glm::cross(camera->GetRight(), frontFar - camera->GetUp() * halfHeight));
	down.SetPositionAndNormal(camera->GetPosition(), glm::cross(frontFar + camera->GetUp() * halfHeight, camera->GetRight()));
}

void OcclusionCulling::SetCamera(Camera* cam)
{
	camera = cam;
}