#include "frustrumCulling.h"

namespace MikkaiEngine
{
	Camera2* frustrumCulling::cam = nullptr;

	plane frustrumCulling::up    = plane();
	plane frustrumCulling::down  = plane();
	plane frustrumCulling::left  = plane();
	plane frustrumCulling::right = plane();
	plane frustrumCulling::front = plane();
	plane frustrumCulling::back  = plane();

	frustrumCulling::frustrumCulling()
	{
		cam = nullptr;

		up    = plane();
		down  = plane();
		left  = plane();
		right = plane();
		front = plane();
		back  = plane();
	}

	frustrumCulling::~frustrumCulling()
	{
	}

	void frustrumCulling::Init(Camera2* camera)
	{
		cam = camera;
	}

	void frustrumCulling::Update()
	{
		float fov = cam->getFOV();
		float aspect = cam->getAspect();

		float halfheight = cam->getFar() * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = cam->getFar() * cam->GetFront();

		back.SetPositionAndNormal(cam->getPos() + cam->getNear() * cam->GetFront(), cam->GetFront());
		front.SetPositionAndNormal(cam->getPos() + frontFar, - cam->GetFront());
		right.SetPositionAndNormal(cam->getPos(), glm::cross(cam->GetUp(), frontFar + cam->GetRight() * halfWidth));
		left.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar - cam->GetRight() * halfWidth, cam->GetUp()));
		up.SetPositionAndNormal(cam->getPos(), glm::cross(cam->GetRight(), frontFar - cam->GetUp() * halfheight));
		down.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar + cam->GetUp() * halfheight, cam->GetRight()));
	}

	void frustrumCulling::SetCamera(Camera2* camera)
	{
		cam = camera;
	}
}