#include "occlusionCulling.h"

namespace MikkaiEngine
{
	Camera2* OcclusionCulling::cam = nullptr;

	glm::vec3 OcclusionCulling::pointBack = glm::vec3();
	glm::vec3 OcclusionCulling::pointFront = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointTopRight = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomLeft = glm::vec3();
	glm::vec3 OcclusionCulling::pointBottomRight = glm::vec3();

	plane OcclusionCulling::up    = plane();
	plane OcclusionCulling::down  = plane();
	plane OcclusionCulling::left  = plane();
	plane OcclusionCulling::right = plane();
	plane OcclusionCulling::front = plane();
	plane OcclusionCulling::back  = plane();

	OcclusionCulling::OcclusionCulling()
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

	OcclusionCulling::~OcclusionCulling()
	{
	}

	void OcclusionCulling::Init(Camera2* camera)
	{
		cam = camera;
	}

	void OcclusionCulling::Update()
	{
		float fov = cam->getFOV();
		float aspect = cam->getAspect();

		float halfheight = cam->getFar() * (glm::tan((fov * .5f) * glm::pi<float>() / 180.f));
		float halfWidth = halfheight * aspect;
		glm::vec3 frontFar = cam->getFar() * cam->GetFront();

		back.SetPositionAndNormal(cam->getPos() + cam->getNear() * cam->GetFront(), cam->GetFront());
		front.SetPositionAndNormal(cam->getPos() + frontFar, -cam->GetFront());
		right.SetPositionAndNormal(cam->getPos(), glm::cross(cam->GetUp(), frontFar + cam->GetRight() * halfWidth));
		left.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar - cam->GetRight() * halfWidth, cam->GetUp()));
		up.SetPositionAndNormal(cam->getPos(), glm::cross(cam->GetRight(), frontFar - cam->GetUp() * halfheight));
		down.SetPositionAndNormal(cam->getPos(), glm::cross(frontFar + cam->GetUp() * halfheight, cam->GetRight()));
	}
	bool OcclusionCulling::IsOnView(std::vector<glm::vec3> aabbPositions)
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


	void OcclusionCulling::SetCamera(Camera2* camera)
	{
		cam = camera;
	}
}