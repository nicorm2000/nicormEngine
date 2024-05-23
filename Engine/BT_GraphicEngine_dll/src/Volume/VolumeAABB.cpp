#include "VolumeAABB.h"
#include "OcclusionCulling/OcclusionCulling.h"

const int lineVertTam = 24;

VolumeAABB::VolumeAABB() : Volume()
{
	center = glm::vec3();
	extents = glm::vec3();
}

VolumeAABB::VolumeAABB(glm::vec3 min, glm::vec3 max) : Volume()
{
	center = glm::vec3((max + min) * .5f);
	extents = glm::vec3(max.x - center.x, max.y - center.y, max.z - center.z);
}

VolumeAABB::VolumeAABB(glm::vec3 center, float extX, float extY, float extZ)
{
	this->center = center;
	extents = glm::vec3(extX, extY, extZ);
}

VolumeAABB::~VolumeAABB()
{
}

void VolumeAABB::Init(Renderer* renderer)
{
	lines = new Line(GetVertexs(), renderer);
	lines->Init();
}

void VolumeAABB::Draw(glm::mat4 model)
{
	lines->Draw(model);
}

bool VolumeAABB::IsOnFrustum()
{
	return (IsOnPlane(OcclusionCulling::left) && IsOnPlane(OcclusionCulling::right) &&
			IsOnPlane(OcclusionCulling::up) && IsOnPlane(OcclusionCulling::down) &&
			IsOnPlane(OcclusionCulling::back) && IsOnPlane(OcclusionCulling::front));
}

bool VolumeAABB::IsOnPlane(Plane plane)
{
	float r = extents.x * abs(plane.GetNormal().x) + extents.y * abs(plane.GetNormal().y) + extents.z * abs(plane.GetNormal().z);
	return -r <= plane.GetDistanceToPoint(center);
}

vector<Vertex> VolumeAABB::GetVertexs()
{
	glm::vec3 vertice[lineVertTam];
	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[5] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[6] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };

	vertice[8] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[9] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[10] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[11] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	vertice[12] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[13] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[14] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	vertice[15] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };

	vertice[16] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[17] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[18] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[19] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[20] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[21] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[22] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[23] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };

	vector<Vertex> vertexs = vector<Vertex>();

	for (int i = 0; i < lineVertTam; i++)
	{
		Vertex vertex;
		vertex.Position = vertice[i];
		vertexs.push_back(vertex);
	}

	return vertexs;
}

void VolumeAABB::SetGlobalVolume(Volume* volume, glm::mat4 model)
{
	VolumeAABB* volumeAABB = static_cast<VolumeAABB*>(volume);

	// Global scale thanks to our transform
	glm::vec3 globalCenter{model * glm::vec4(volumeAABB->center, 1.f)};
	 
	// Scaled orientation
	glm::vec3 right = model[0] * volumeAABB->extents.x;
	glm::vec3 up = model[1] * volumeAABB->extents.y;
	glm::vec3 forward = model[2] * volumeAABB->extents.z;

	float newIi = abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
				  abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
				  abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	float newIj = abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
				  abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
				  abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	float newIk = abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
				  abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
				  abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	SetVolume(globalCenter, newIi, newIj, newIk);
}

void VolumeAABB::SetVolume(glm::vec3 center, float extX, float extY, float extZ)
{
	this->center = center;
	extents = glm::vec3(extX, extY, extZ);
}