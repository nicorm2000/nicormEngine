//#ifndef SPHERE_H
//#define SPHERE_H
//#include "BoundingVolume/BoundingVolume.h"
//#include "Model/Model2.h"
//namespace MikkaiEngine
//{
//	struct Sphere : public volume
//	{
//		glm::vec3 center{ 0.f, 0.f, 0.f };
//		float radius{ 0.f };
//
//		Sphere(glm::vec3& inCenter, float inRadius): volume{}, center{ inCenter }, radius{ inRadius }
//		{}
//
//		bool isOnOrForwardPlan(Plane& plan)
//		{
//			return plan.getSignedDistanceToPlan(center) > -radius;
//		}
//
//		bool isOnFrustum(Frustum& camFrustum, Transform& transform)
//		{
//			//Get global scale thanks to our transform
//			glm::vec3 globalScale = transform.getGlobalScale();
//
//			//Get our global center with process it with the global model matrix of our transform
//			glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };
//
//			//To wrap correctly our shape, we need the maximum scale scalar.
//			float maxScale = std::max(std::max(globalScale.x, globalScale.y), globalScale.z);
//
//			//Max scale is assuming for the diameter. So, we need the half to apply it to our radius
//			Sphere globalSphere(globalCenter, radius * (maxScale * 0.5f));
//
//			//Check Firstly the result that have the most chance to faillure to avoid to call all functions.
//			return (globalSphere.isOnOrForwardPlan(camFrustum.leftFace) &&
//				globalSphere.isOnOrForwardPlan(camFrustum.rightFace) &&
//				globalSphere.isOnOrForwardPlan(camFrustum.farFace) &&
//				globalSphere.isOnOrForwardPlan(camFrustum.nearFace) &&
//				globalSphere.isOnOrForwardPlan(camFrustum.topFace) &&
//				globalSphere.isOnOrForwardPlan(camFrustum.bottomFace));
//		};
//	};
//	Sphere generateSphereBV(Model& model)
//	{
//		glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
//		glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
//		for (std::list<Mesh2*>::iterator it = model.meshes.begin(); it != model.meshes.end(); it++)
//		{
//			MeshData* data = (**it).data;
//			for (auto&& vertex : data->vertices)
//			{
//				minAABB.x = std::min(minAABB.x, vertex.Position.x);
//				minAABB.y = std::min(minAABB.y, vertex.Position.y);
//				minAABB.z = std::min(minAABB.z, vertex.Position.z);
//
//				maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
//				maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
//				maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
//			}
//		}
//
//		return Sphere((maxAABB + minAABB) * 0.5f, (glm::length(minAABB - maxAABB)));
//	}
//}
//#endif // !SPHERE_H
