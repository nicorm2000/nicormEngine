#include "Entity.h"

float deg2rad = ( 3.14f* 2.0f) / 360.0f;
int Entity::CuantityEntitys = 0;
std::list<Entity*> Entity::EntitysLists;
Entity::Entity() {
	
	_renderer = nullptr;

	transform.position = glm::vec3(0.f);
	transform.eulerAngles = glm::vec3(0.f);
	transform.scale = glm::vec3(1.f);
	transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

	transform.localPosition = glm::vec3(0.f);
	transform.localEulerAngles = glm::vec3(0.f);
	transform.localScale = glm::vec3(1.f);
	transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

	transform.forward = glm::vec3(0.f);
	transform.up = glm::vec3(0.f);
	transform.right = glm::vec3(0.f);

	matrix.model = glm::mat4(1.f);
	matrix.translate = glm::mat4(1.f);
	matrix.rotationX = glm::mat4(1.f);
	matrix.rotationY = glm::mat4(1.f);
	matrix.rotationZ = glm::mat4(1.f);
	matrix.scale = glm::mat4(1.f);

	UpdateMatrixData();
}
Entity::Entity(Renderer* renderer)
{
	_renderer = renderer;

	transform.position = glm::vec3(0.f);
	transform.eulerAngles = glm::vec3(0.f);
	transform.scale = glm::vec3(1.f);
	transform.rotation = glm::quat(0.f, 0.f, 0.f, 1.f);

	transform.localPosition = glm::vec3(0.f);
	transform.localEulerAngles = glm::vec3(0.f);
	transform.localScale = glm::vec3(1.f);
	transform.localRotation = glm::quat(0.f, 0.f, 0.f, 1.f);

	transform.forward = glm::vec3(0.f);
	transform.up = glm::vec3(0.f);
	transform.right = glm::vec3(0.f);

	matrix.model = glm::mat4(1.f);
	matrix.translate = glm::mat4(1.f);
	matrix.rotationX = glm::mat4(1.f);
	matrix.rotationY = glm::mat4(1.f);
	matrix.rotationZ = glm::mat4(1.f);
	matrix.scale = glm::mat4(1.f);

	UpdateMatrixData();
	EntitysLists.push_front(this);
	_name = "Entity " + std::to_string(CuantityEntitys);
	CuantityEntitys++;
}
Entity::~Entity() {

}
void Entity::SetUniforms()
{
	_renderer->SetLocation(_locationPosition, "aPos");
	_renderer->SetLocation(_locationTexCoord, "aTex");
	_renderer->SetLocation(_locationNormal, "aNor");
}
void Entity::UpdateMatrixData() {
	matrix.model = matrix.translate * matrix.rotationX * matrix.rotationY * matrix.rotationZ * matrix.scale;
}

glm::quat EulerToQuat(glm::vec3 euler) {
	euler *= deg2rad;

	float cy = cos(euler.z * 0.5);
	float sy = sin(euler.z * 0.5);
	float cp = cos(euler.x * 0.5);
	float sp = sin(euler.x * 0.5);
	float cr = cos(euler.y * 0.5);
	float sr = sin(euler.y * 0.5);

	glm::quat q;
	q.w = cr * cp * cy + sr * sp * sy;
	q.x = cr * sp * cy + sr * cp * sy;
	q.y = sr * cp * cy - cr * sp * sy;
	q.z = cr * cp * sy - sr * sp * cy;
	return q;
}

glm::vec3 QuatXVec(glm::quat quat, glm::vec3 vec) {
	float x2 = quat.x * 2.0f;
	float y2 = quat.y * 2.0f;
	float z2 = quat.z * 2.0f;
	float xx2 = quat.x * x2;
	float yy2 = quat.y * y2;
	float zz2 = quat.z * z2;
	float xy2 = quat.x * y2;
	float xz2 = quat.x * z2;
	float yz2 = quat.y * z2;
	float wx2 = quat.w * x2;
	float wy2 = quat.w * y2;
	float wz2 = quat.w * z2;

	glm::vec3 res;
	res.x = (1.0f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.0f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.0f - (xx2 + yy2)) * vec.z;
	return res;
}
//------------set Pos----------------------------
void Entity::SetPos(float x, float y) {
	SetPos(x, y, getPos().z);
}
void Entity::SetPos(glm::vec2 pos) {
	SetPos(pos.x, pos.y);
}
void Entity::SetPos(float x, float y, float z)
{
	transform.lastPosition = transform.position;
	transform.position = { x, y, z };
	matrix.translate = glm::translate(glm::mat4(1.0f), transform.position);
	UpdateMatrixData();
	UpdateTransform();
}
void Entity::SetPos(glm::vec3 pos)
{
	SetPos(pos.x, pos.y, pos.z);
}
//-----------------------------------------------
//------------set Rot----------------------------

void Entity::SetRotations(glm::vec3 rot)
{

	transform.rotation = rot;
	transform.localRotation = rot;
	transform.eulerAngles = rot;
	matrix.rotationX = glm::rotate(glm::mat4(1.f), glm::radians(rot.x), glm::vec3(1.f, 0.f, 0.f));
	matrix.rotationY = glm::rotate(glm::mat4(1.f), glm::radians(rot.y), glm::vec3(0.f, 1.f, 0.f));
	matrix.rotationZ = glm::rotate(glm::mat4(1.f), glm::radians(rot.z), glm::vec3(0.f, 0.f, 1.f));

	UpdateMatrixData();
	UpdateTransform();
}
void Entity::SetRotX(float x) {
	SetRotations(glm::vec3(x, transform.eulerAngles.y, transform.eulerAngles.z));
}
void Entity::SetRotations(float x, float y, float z)
{
	SetRotations(glm::vec3(x, y, z));
}

void Entity::SetRotY(float y) {
	SetRotations(glm::vec3(transform.eulerAngles.x, y, transform.eulerAngles.z));
}
void Entity::SetRotZ(float z) {
	SetRotations(glm::vec3(transform.eulerAngles.x, transform.eulerAngles.y, z));
}
void Entity::SetScale(glm::vec3 scale4)
{
	transform.scale = scale4;
	matrix.scale = glm::scale4(glm::mat4(1.0f), scale4);
	UpdateMatrixData();
}
void Entity::SetScale(float x, float y)
{
	SetScale(glm::vec3(x, y, transform.scale.z));
}
void Entity::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}
void Entity::SetScale(float newScale)
{
	SetScale(glm::vec3(newScale, newScale, newScale));
}

void Entity::SetColor(float x, float y, float z, float w)
{
	_color.SetColor(x, y, z, w);
}

void Entity::SetColor(float x, float y, float z)
{
	_color.SetColor(x, y, z);
}

glm::vec3 Entity::getPos()
{
	return transform.position;
}

glm::vec3 Entity::getRot()
{
	return transform.eulerAngles;
}

glm::vec3 Entity::getScale()
{
	return transform.scale;
}
glm::vec3 Entity::getLastPos()
{
	return transform.lastPosition;
}
glm::vec3 Entity::getColor()
{
	return _color.GetColorV3();
}
void Entity::Draw(uint shaderId)
{
	//_renderer->DrawM(model, _vao, _vbo, _ebo, indicesTam, tam, vertex, shaderId);
}

void Entity::UpdateTransform()
{
	transform.rotation = EulerToQuat(transform.eulerAngles);
	transform.forward = QuatToVec(transform.rotation, glm::vec3(0.f, 0.f, 1.f));
	transform.up = QuatToVec(transform.rotation, glm::vec3(0.f, 1.f, 0.f));
	transform.right = QuatToVec(transform.rotation, glm::vec3(1.f, 0.f, 0.f));
}


glm::vec3 Entity::QuatToVec(glm::quat quat, glm::vec3 vec)
{
	float x2 = quat.x * 2.f;
	float y2 = quat.y * 2.f;
	float z2 = quat.z * 2.f;
	float xx2 = quat.x * x2;
	float yy2 = quat.y * y2;
	float zz2 = quat.z * z2;
	float xy2 = quat.x * y2;
	float xz2 = quat.x * z2;
	float yz2 = quat.y * z2;
	float wx2 = quat.w * x2;
	float wy2 = quat.w * y2;
	float wz2 = quat.w * z2;

	glm::vec3 res;
	res.x = (1.f - (yy2 + zz2)) * vec.x + (xy2 - wz2) * vec.y + (xz2 + wy2) * vec.z;
	res.y = (xy2 + wz2) * vec.x + (1.f - (xx2 + zz2)) * vec.y + (yz2 - wx2) * vec.z;
	res.z = (xz2 - wy2) * vec.x + (yz2 + wx2) * vec.y + (1.f - (xx2 + yy2)) * vec.z;
	return res;
}

