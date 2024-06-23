//#ifndef FRUSTRUM_H
//#define FRUSTRUM_H
//#include "Plan/Plan.h"
//#include "Transform/Transform.h"
//namespace MikkaiEngine
//{
//	struct Frustum
//	{
//		Plane topFace;
//		Plane bottomFace;
//
//		Plane rightFace;
//		Plane leftFace;
//
//		Plane farFace;
//		Plane nearFace;
//
//		Frustum(Transform* cam, float aspect, float fovY, float zNear, float zFar)
//		{
//			float halfVSide = zFar * tanf(fovY * .5f);
//			float halfHSide = halfVSide * aspect;
//			glm::vec3 frontMultFar = zFar * cam->getForward();
//			nearFace =   { cam->getposition() + zNear * cam->getForward(), cam->getForward()					};
//			farFace =    { cam->getposition() + frontMultFar, -cam->getForward()									};
//			rightFace =  { cam->getposition(), glm::cross(cam->GetUp(), frontMultFar + cam->GetRight() * halfHSide) };
//			leftFace =   { cam->getposition(), glm::cross(frontMultFar - cam->GetRight() * halfHSide, cam->GetUp()) };
//			topFace =    { cam->getposition(), glm::cross(cam->GetRight(), frontMultFar - cam->GetUp() * halfVSide) };
//			bottomFace = { cam->getposition(), glm::cross(frontMultFar + cam->GetUp() * halfVSide, cam->GetRight()) };
//		}
//	};
//}
//#endif // !FRUSTRUM_H
