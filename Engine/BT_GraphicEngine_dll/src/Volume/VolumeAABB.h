#ifndef VOLUME_AABB_H
#define	VOLUME_AABB_H

#include <glew.h>
#include <glfw3.h>
#include "Export.h"
#include "Volume/Volume.h"
using namespace std;

class DllApi VolumeAABB : public Volume
{
public:
	VolumeAABB();
	VolumeAABB(glm::vec3 min, glm::vec3 max);
	VolumeAABB(glm::vec3 center, float extX, float extY, float extZ);
	~VolumeAABB();

	void Init(Renderer* renderer) override;
	void Draw(glm::mat4 model) override;

	bool IsOnFrustum() override;
	bool IsOnPlane(Plane plane) override;
	vector<Vertex> GetVertexs() override;
	void SetGlobalVolume(Volume* volume, glm::mat4 model) override;
	void SetVolume(glm::vec3 center, float extX, float extY, float extZ);

	glm::vec3 center;
	glm::vec3 extents;
};

#endif