#ifndef AABB_H
#define AABB_H
#include "BoundingVolume/BoundingVolume.h"
#include <array>
namespace MikkaiEngine
{
	class GraficosEngine_API aabb : public volume
	{
	public:
		aabb();
		aabb(glm::vec3 min, glm::vec3 max);
		aabb(glm::vec3 center, float extX, float extY, float extZ);
		void update(glm::vec3 min, glm::vec3 max);
		~aabb();

		aabb getGlobalVolume(glm::mat4 worldModel);

		bool isOnFrustum(glm::mat4 worldModel) override;

		glm::vec3 center;
		glm::vec3 extents;
		glm::vec3 min;
		glm::vec3 max;
		bool isOnPlane(plane plane) override;
	private:
	};
}
#endif // !aabb
