#ifndef OCCLUSION_CULLING_H
#define OCCLUSION_CULLING_H

#include "Exports/Exports.h"
#include "Camera2/Camera2.h"
#include "Plan/Plane.h"
#include <vector>

namespace MikkaiEngine
{
	class GraficosEngine_API OcclusionCulling
	{
	public:
		OcclusionCulling();
		~OcclusionCulling();

		static void Init(Camera2* camera);
		static void Update();

		static bool IsOnView(std::vector<glm::vec3> aabb);
		static void SetCamera(Camera2* camera);


		static plane up;
		static plane down;
		static plane left;
		static plane right;
		static plane front;
		static plane back;

	private:
		static Camera2* cam;

		static glm::vec3 pointBack;
		static glm::vec3 pointFront;
		static glm::vec3 pointTopLeft;
		static glm::vec3 pointTopRight;
		static glm::vec3 pointBottomLeft;
		static glm::vec3 pointBottomRight;
	};
}

#endif //!OCCLUSION_CULLING_H