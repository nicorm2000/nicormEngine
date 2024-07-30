#include "frustrumCulling.h"

namespace MikkaiEngine
{
	Camera2* frustrumCulling::cam = nullptr;

	glm::vec3 frustrumCulling::pointBack = glm::vec3();
	glm::vec3 frustrumCulling::pointFront = glm::vec3();
	glm::vec3 frustrumCulling::pointTopLeft = glm::vec3();
	glm::vec3 frustrumCulling::pointTopRight = glm::vec3();
	glm::vec3 frustrumCulling::pointBottomLeft = glm::vec3();
	glm::vec3 frustrumCulling::pointBottomRight = glm::vec3();

	plane frustrumCulling::up    = plane();
	plane frustrumCulling::down  = plane();
	plane frustrumCulling::left  = plane();
	plane frustrumCulling::right = plane();
	plane frustrumCulling::front = plane();
	plane frustrumCulling::back  = plane();

	frustrumCulling::frustrumCulling()
	{
		cam = nullptr;

		pointBack = glm::vec3();
		pointFront = glm::vec3();
		pointTopLeft = glm::vec3();
		pointTopRight = glm::vec3();
		pointBottomLeft = glm::vec3();
		pointBottomRight = glm::vec3();

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
	bool frustrumCulling::IsOnView(std::vector<glm::vec3> aabbPositions)
	{
		for (short i = 0; i < aabbPositions.size(); i++)
		{
			if (back.GetSide(aabbPositions[i]) && front.GetSide(aabbPositions[i]) && right.GetSide(aabbPositions[i])
				&& left.GetSide(aabbPositions[i]) && up.GetSide(aabbPositions[i]) && down.GetSide(aabbPositions[i]))
			{
				return true;
			}
		}

		return false;
	}


	void frustrumCulling::SetCamera(Camera2* camera)
	{
		cam = camera;
	}
}