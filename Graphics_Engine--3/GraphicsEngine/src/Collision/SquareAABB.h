#ifndef SQUAREAABB_H
#define SQUAREAABB_H
#include "BoundingVolume/BoundingVolume.h"
namespace MikkaiEngine
{
	struct SquareAABB : public volume
	{
		glm::vec3 center{ 0.f, 0.f, 0.f };
		float extent{ 0.f };

		SquareAABB(const glm::vec3& inCenter, float inExtent)
			: volume{}, center{ inCenter }, extent{ inExtent }
		{}

		bool isOnOrForwardPlan(Plane& plan)
		{
			// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
			const float r = extent * (std::abs(plan.normal.x) + std::abs(plan.normal.y) + std::abs(plan.normal.z));
			return -r <= plan.getSignedDistanceToPlan(center);
		}

		bool isOnFrustum(Frustum& camFrustum,Transform& transform)
		{
			//Get global scale thanks to our transform
			glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

			// Scaled orientation
			glm::vec3 right = transform.getRight() * extent;
			glm::vec3 up = transform.getUp() * extent;
			glm::vec3 forward = transform.getForward() * extent;

			float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

			float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

			float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
				std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

			SquareAABB globalAABB(globalCenter, std::max(std::max(newIi, newIj), newIk));

			return (globalAABB.isOnOrForwardPlan(camFrustum.leftFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.rightFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.topFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.bottomFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.nearFace) &&
				globalAABB.isOnOrForwardPlan(camFrustum.farFace));
		};
	};

}
#endif // SQUAREAABB_H
