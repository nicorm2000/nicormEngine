#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include "Plan/Plane.h"

namespace MikkaiEngine
{
	class GraficosEngine_API volume
	{
	public:
		volume() { };
		~volume() { };

		virtual bool isOnFrustum(glm::mat4 worldModel) = 0;

	protected:
		virtual bool isOnPlane(plane plane) = 0;
	};
}
#endif
