#include "Transform.h"
namespace MikkaiEngine
{
	
	vec3 QuatToVec(glm::quat quat, glm::vec3 vec)
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

	quat EulerToQuat(vec3 euler)
	{
		float deg2rad = (3.14f * 2.0f) / 360.0f;
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
	Transform::Transform() : Component(this)
	{
		m_pos = vec3(0, 0, 0);
		m_eulerRot = vec3(0, 0, 0);
		m_scale = vec3(1);

		worldModel  = mat4(1);
		localModel  = mat4(1);
		parentModel = mat4(1);

		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}
	Transform::Transform(GameObject* gameObject) : Component(this, gameObject)
	{
		m_pos = vec3(0, 0, 0);
		m_eulerRot = vec3(0, 0, 0);
		m_scale = vec3(1);

		worldModel = mat4(1);
		localModel = mat4(1);
		parentModel = mat4(1);

		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}
	Transform::Transform(GameObject* gameObject,Entity2* ourEntity) : Component(this,gameObject, ourEntity)
	{
		 m_pos = vec3(0,0,0);
		 m_eulerRot = vec3(0,0,0);
		 m_scale = vec3(1);
		 
		 worldModel = mat4(1);
		 localModel = mat4(1);
		 parentModel = mat4(1);
		
		updateTransformRotation();
		AddDescription("-> ||Transform|| ");
	}

	Transform::~Transform()
	{
	}

	void Transform::setForward(vec3 v)
	{
		localModel[2].x = -v.x;
		localModel[2].y = -v.y;
		localModel[2].z = -v.z;
		localModel[2].w = -0;
	}
	void Transform::setRight(vec3 v)
	{
		localModel[0].x = v.x;
		localModel[0].y = v.y;
		localModel[0].z = v.z;
		localModel[0].w = 0;
	};
	void Transform::setUp(vec3 v)
	{
		localModel[1].x = v.x;
		localModel[1].y = v.y;
		localModel[1].z = v.z;
		localModel[1].w = 0;
	}

	void Transform::updateLocalModelMatrix()
	{
		updateTransformRotation();
		const mat4 transformX = glm::rotate(mat4(1.0f),(m_eulerRot.x), vec3(1.0f, 0.0f, 0.0f));
		const mat4 transformY = glm::rotate(mat4(1.0f),(m_eulerRot.y), vec3(0.0f, 1.0f, 0.0f));
		const mat4 transformZ = glm::rotate(mat4(1.0f),(m_eulerRot.z), vec3(0.0f, 0.0f, 1.0f));
		// Y * X * Z
		const mat4 roationMatrix = transformX * transformY * transformZ;
		// translation * rotation * scale (also know as TRS matrix)
		localModel = glm::translate(glm::mat4(1.0f), m_pos) * roationMatrix * glm::scale4(mat4(1.0f), m_scale);
	}

	void Transform::updateTransformRotation()
	{
		quat rotation = EulerToQuat(m_eulerRot);
		vec3 forward = QuatToVec(rotation, vec3(0.f, 0.f, 1.f));
		vec3 up = QuatToVec(rotation, vec3(0.f, 1.f, 0.f));
		vec3 right = QuatToVec(rotation, vec3(1.f, 0.f, 0.f));
		setForward(forward);
		setUp(up);
		setRight(right);
	}

	glm::vec3 Transform::getRight()
	{
		return worldModel[0];
	}


	glm::vec3 Transform::getUp()
	{
		return worldModel[1];
	}

	glm::vec3 Transform::getBackward()
	{
		return worldModel[2];
	}

	glm::vec3 Transform::getForward()
	{
		return -worldModel[2];
	}
	void Transform::setRotX(float x)
	{
		m_eulerRot.x = x;
		glm::vec3 axis;

		axis[1] = axis[2] = 0.0f;
		axis[0] = 1.0f;

		//updateLocalModelMatrix();
	}
	void Transform::setRotY(float y)
	{
		m_eulerRot.y = y;
		glm::vec3 axis;

		axis[0] = axis[2] = 0.0f;
		axis[1] = 1.0f;

		//updateLocalModelMatrix();
	}
	void Transform::setRotZ(float z)
	{
		m_eulerRot.z = z;
		glm::vec3 axis;

		axis[0] = axis[1] = 0.0f;
		axis[2] = 1.0f;

		//updateLocalModelMatrix();
	}
}

