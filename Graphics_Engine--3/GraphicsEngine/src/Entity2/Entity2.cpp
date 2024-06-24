#include "Entity2.h"
namespace MikkaiEngine
{
	int Entity2::CuantityEntitys = 0;
	std::list<Entity2*> Entity2::EntitysLists;
	Entity2::Entity2(Renderer* renderer) : GameObject(this)
	{
		_renderer = renderer;
		_locationPosition =0;
		_locationNormal	  =0;
		_locationTexCoord =0;
		_color = glm::vec3(1, 1, 1);
		EntitysLists.push_front(this);
		 SetnameOBJ("Entity " + std::to_string(CuantityEntitys));
		 setName("Entity " + std::to_string(CuantityEntitys));
		 AddDescription("-> || " + getName() + " || ");
		CuantityEntitys++;
		meshes = vector<Mesh*>();
		parent = nullptr;
		volume = nullptr;
		generateAABB();
	}
	Entity2::~Entity2()
	{
		EntitysLists.remove(this);
	}

	void Entity2::SetPos(glm::vec3 pos)
	{
		getTransform()->setposition(pos);
		updateModelMatrix();
	}

	void Entity2::SetRotations(glm::vec3 rotation)
	{
		getTransform()->seteulerAngles(rotation);
		updateModelMatrix();
	}

	void Entity2::SetScale(glm::vec3 v)
	{
		getTransform()->setlocalScale(v);
		updateModelMatrix();
	}

	void Entity2::SetMatrix(glm::mat4 mat)
	{
		SetPos(GetPos(mat));
		SetRotRadian(GetRot(mat));
		SetScale(GetScale(mat));
	}

	mat4 Entity2::getGlobMat()
	{
		if (parent == nullptr)
			return getTransform()->getLocalModel();
		else
			getGlobMat(parent) * getTransform()->getLocalModel();
	}
	mat4 Entity2::getGlobMat(Entity2* matParent)
	{
		if (matParent->parent == nullptr)
			return getTransform()->getLocalModel();
		else
			return getGlobMat(matParent->parent) * getTransform()->getLocalModel();
	}
	glm::vec3 Entity2::GetPosGlobalMat()
	{
		vec3 text1 = GetPos(getTransform()->getLocalModel());
		vec3 text2 = GetPos(getTransform()->getLocalModel());
		text2 = GetPos(getTransform()->getWorldModel());


		return GetPos(getTransform()->getWorldModel());
	}

	void Entity2::SetRot(glm::vec3 rot)
	{
		getTransform()->seteulerAngles(rot);

		updateModelMatrix();

		getTransform()->updateLocalModelMatrix();
	}

	void Entity2::SetRotRadian(glm::vec3 rot)
	{
		getTransform()->setRotX(glm::radians(rot.x));
		getTransform()->setRotY(glm::radians(rot.y));
		getTransform()->setRotZ(glm::radians(rot.z));
		updateModelMatrix();
	}




	glm::vec3 Entity2::GetPos(glm::mat4 mat)
	{
		return glm::vec3(mat[3][0], mat[3][1], mat[3][2]);
	}

	glm::vec3 Entity2::GetRot(glm::mat4 mat)
	{
		return ToEulerRad(GetRotationByMatrix(mat));
	}
	glm::quat Entity2::GetRotationByMatrix(glm::mat4 mat)
	{
		glm::vec3 s = GetScale(mat);

		float m00 = mat[0].x / s.x;
		float m01 = mat[0].y / s.y;
		float m02 = mat[0].z / s.z;
		float m10 = mat[1].x / s.x;
		float m11 = mat[1].y / s.y;
		float m12 = mat[1].z / s.z;
		float m20 = mat[2].x / s.x;
		float m21 = mat[2].y / s.y;
		float m22 = mat[2].z / s.z;

		glm::quat q = glm::quat();
		q.w = glm::sqrt(glm::max(0.f, 1.f + m00 + m11 + m22)) / 2.f;
		q.x = glm::sqrt(glm::max(0.f, 1.f + m00 - m11 - m22)) / 2.f;
		q.y = glm::sqrt(glm::max(0.f, 1.f - m00 + m11 - m22)) / 2.f;
		q.z = glm::sqrt(glm::max(0.f, 1.f - m00 - m11 + m22)) / 2.f;
		q.x *= glm::sign(q.x * (m21 - m12));
		q.y *= glm::sign(q.y * (m02 - m20));
		q.z *= glm::sign(q.z * (m10 - m01));

		float qMagnitude = glm::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
		q.w /= qMagnitude;
		q.x /= qMagnitude*-1;
		q.y /= qMagnitude*-1;
		q.z /= qMagnitude*-1;

		return q;
	}

	Entity2* Entity2::GetNode(std::string nodeName)
	{
		if (getName() == nodeName)
		{
			return this;
		}

		if (children.size() > 0)
		{
			Entity2* node = nullptr;
			for (int i = 0; i < children.size(); i++)
			{
				node = children[i]->GetNode(nodeName);

				if (node != nullptr) break;
			}
			return node;
		}
		return nullptr;
	}
	Entity2* Entity2::GetNode(std::string nodeName, std::string data)
	{
		if (getName().find(nodeName)!= -1 && getName().find(data)!=-1)
		{
			return this;
		}

		if (children.size() > 0)
		{
			Entity2* node = nullptr;
			for (int i = 0; i < children.size(); i++)
			{
				node = children[i]->GetNode(nodeName);

				if (node != nullptr) break;
			}
			return node;
		}
		return nullptr;
	}


	glm::vec3 Entity2::GetScale(glm::mat4 mat)
	{
		glm::vec4 m0 = glm::vec4(mat[0].x, mat[0].y, mat[0].z, mat[0].w);
		glm::vec4 m1 = glm::vec4(mat[1].x, mat[1].y, mat[1].z, mat[1].w);
		glm::vec4 m2 = glm::vec4(mat[2].x, mat[2].y, mat[2].z, mat[2].w);
		return glm::vec3(glm::length(m0), glm::length(m1), glm::length(m2));

	}

	glm::vec3 Entity2::ToEulerRad(glm::quat rot)
	{
		float sqw = rot.w * rot.w;
		float sqx = rot.x * rot.x;
		float sqy = rot.y * rot.y;
		float sqz = rot.z * rot.z;
		float unit = sqx + sqy + sqz + sqw;
		float test = rot.x * rot.w - rot.y * rot.z;

		glm::vec3 v = glm::vec3();

		if (test > 0.4995f * unit)
		{
			v.y = 2.f * atan2(rot.y, rot.x);
			v.x = glm::pi<float>() / 2.f;
			v.z = 0.f;

			return NormalizeAngles(v * 57.29578f);
		}
		if (test < -0.4995f * unit)
		{
			v.y = -2.f * atan2(rot.y, rot.x);
			v.x = -glm::pi<float>() / 2.f;
			v.z = 0.f;

			return NormalizeAngles(v * 57.29578f);
		}

		glm::vec4 q = glm::vec4(rot.w, rot.z, rot.x, rot.y);
		v.y = atan2(2.f * q.x * q.w + 2.f * q.y * q.z, 1.f - 2.f * (q.z * q.z + q.w * q.w));
		v.x = asin(2.f * (q.x * q.z - q.w * q.y));
		v.z = atan2(2.f * q.x * q.y + 2.f * q.z * q.w, 1.f - 2.f * (q.y * q.y + q.z * q.z));

		return NormalizeAngles(v * 57.29578f);
	}

	glm::vec3 Entity2::NormalizeAngles(glm::vec3 angles)
	{
		angles.x = NormalizeAngle(angles.x);
		angles.y = NormalizeAngle(angles.y);
		angles.z = NormalizeAngle(angles.z);

		return angles;
	}

	float Entity2::NormalizeAngle(float angle)
	{
		while (angle > 360.f)
			angle -= 360.f;
		while (angle < 0.f)
			angle += 360.f;

		return angle;
	}

	void Entity2::DebugInfo()
	{
		cout << endl << "-----ExampleDebugInfoEntity2------" << endl;
		Transform* transform = getTransform();
		cout << "pos: " + VecToString::vec3toString(transform->getposition())		<< std::endl;
		cout << "rot: " + VecToString::vec3toString(transform->geteulerAngles())		<< std::endl;
		cout << "sca: " + VecToString::vec3toString(transform->getlocalScale())		<< std::endl;
		cout << "for: " + VecToString::vec3toString(transform->getForward())			<< std::endl;
		cout << "up:  " + VecToString::vec3toString(transform->getUp())				<< std::endl;
		cout << "rig: " + VecToString::vec3toString(transform->getRight())			<< std::endl;
	}
	void Entity2::Update()
	{
		//updateSelfAndChild();
	}

	void Entity2::SetUniforms()
	{
		_renderer->SetLocation(_locationPosition, "aPos");
		_renderer->SetLocation(_locationTexCoord, "aTex");
		_renderer->SetLocation(_locationNormal, "aNor");
		_renderer->SetUniform(_uniformColor, "color");
	}
	//bool Entity2::canDrawThisFrame()
	//{
	//	return drawThisFrame;
	//}
	void Entity2::SetMeshes(vector<Mesh*> meshes)
	{
		this->meshes = meshes;

		setAABBView(this->meshes);
	}
	void Entity2::SetParent(Entity2* parent)
	{
		this->parent = parent;
	}
	void Entity2::setChildren(vector<Entity2*> children)
	{
		this->children = children;
	}
	void Entity2::AddChildren(Entity2* children)
	{
		this->children.push_back(children);
	}

	void Entity2::UpdateExtremos() {
		vec3 center = getPos();
		vec3 extend = vec3(0);
		if (getVolume()!=nullptr)
		{
			center = getVolume()->getGlobalVolume(getTransform()->getWorldModel()).center;
			extend = getVolume()->getGlobalVolume(getTransform()->getWorldModel()).extents;
		}
			extremos.clear();
			extremos.push_back(center + vec3(extend.x, extend.y, extend.z));
			extremos.push_back(center + vec3(extend.x, extend.y, -extend.z));
			extremos.push_back(center + vec3(extend.x, -extend.y, extend.z));
			extremos.push_back(center + vec3(-extend.x, extend.y, extend.z));
			extremos.push_back(center + vec3(extend.x, -extend.y, -extend.z));
			extremos.push_back(center + vec3(-extend.x, -extend.y, extend.z));
			extremos.push_back(center + vec3(-extend.x, extend.y, -extend.z));
			extremos.push_back(center + vec3(-extend.x, -extend.y, -extend.z));
		
	
	}
	void Entity2::setDraw()
	{
		for (int i = 0; i < getChildren().size(); i++)
		{
			getChildren()[i]->setWorldModelWithParentModel(getTransform()->getWorldModel());
			getChildren()[i]->setDraw();
		}
		draw();
	}
	void Entity2::Init()
	{
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->Init();
		}
			generateAABB();
	}
	void Entity2::setWorldModelWithParentModel(glm::mat4 parentModel)
	{
		getTransform()->setParentModel(parentModel);

		updateModelMatrix();
	}

	void Entity2::generateAABB()
	{
		if (meshes.size() > 0)
		{
			glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
			glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

			for (int i = 0; i < meshes.size(); i++)
			{
				Mesh* mesh = meshes[i];
				for (int j = 0; j < mesh->vertexs.size(); j++)
				{
					Vertex vertex = mesh->vertexs[j];

					minAABB.x = glm::min(minAABB.x, vertex.Position.x);
					minAABB.y = glm::min(minAABB.y, vertex.Position.y);
					minAABB.z = glm::min(minAABB.z, vertex.Position.z);

					maxAABB.x = glm::max(maxAABB.x, vertex.Position.x);
					maxAABB.y = glm::max(maxAABB.y, vertex.Position.y);
					maxAABB.z = glm::max(maxAABB.z, vertex.Position.z);
				}
			}
			volume = new MikkaiEngine::aabb(minAABB, maxAABB);
			originVolume = new MikkaiEngine::aabb(minAABB, maxAABB);
		}
		else
		{
			volume = new MikkaiEngine::aabb(vec3(0), vec3(0));
			originVolume = new MikkaiEngine::aabb(vec3(0), vec3(0));
		}
	}
	void Entity2::updateAABBWithChildren(Entity2* child)
	{
		if (child->getVolume() != NULL)
		{
			MikkaiEngine::aabb* childVolume = child->getVolume();

			glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
			glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());

			if (volume != NULL)
			{
				minAABB.x = glm::min(volume->min.x, childVolume->min.x);
				minAABB.y = glm::min(volume->min.y, childVolume->min.y);
				minAABB.z = glm::min(volume->min.z, childVolume->min.z);

				maxAABB.x = glm::max(volume->max.x, childVolume->max.x);
				maxAABB.y = glm::max(volume->max.y, childVolume->max.y);
				maxAABB.z = glm::max(volume->max.z, childVolume->max.z);

				volume->update(minAABB, maxAABB);
			}
			else
			{
				volume = new MikkaiEngine::aabb(childVolume->min, childVolume->max);
			}
		}
		//else
		//{
		//	child->updateAABBWithChildren();
		//}
	}

	void Entity2::setTransformations()
	{
		if (meshes.size() > 0)
		{
			volume = new MikkaiEngine::aabb(originVolume->min, originVolume->max);
			volume->update(originVolume->min, originVolume->max);
			
		}

		for (int i = 0; i < getChildren().size(); i++)
		{
			children[i]->setWorldModelWithParentModel(getTransform()->getWorldModel());
			children[i]->setTransformations();

			updateAABBWithChildren(children[i]);
			
			addBoundsToVisualAABB(children[i]->getLocalAABB());
		}
		UpdateExtremos();
	}

	void Entity2::addBoundsToVisualAABB(vector<glm::vec3> childAABB)
	{
		if (childAABB.size() < 1)
		{
			return;
		}
		else if (localAABB.size() < 1)
		{
			localAABB.clear();
			localAABB.push_back(childAABB[0]);
			localAABB.push_back(childAABB[1]);

			aabb.clear();
			aabb.push_back(childAABB[0]);
			aabb.push_back(childAABB[1]);

			return;
		}

		localAABB.clear();
		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);

		if (childAABB[0].x < localAABB[0].x) localAABB[0].x = childAABB[0].x;
		if (childAABB[1].x > localAABB[1].x) localAABB[1].x = childAABB[1].x;
		if (childAABB[0].y < localAABB[0].y) localAABB[0].y = childAABB[0].y;
		if (childAABB[1].y > localAABB[1].y) localAABB[1].y = childAABB[1].y;
		if (childAABB[0].z < localAABB[0].z) localAABB[0].z = childAABB[0].z;
		if (childAABB[1].z > localAABB[1].z) localAABB[1].z = childAABB[1].z;
	}

	void Entity2::setAABBView(vector<Mesh*> meshes)
	{
		if (meshes.size() < 1)
		{
			return;
		}

		aabb.push_back(glm::vec3());
		aabb.push_back(glm::vec3());

		aabb[0].x = aabb[1].x = meshes[0]->vertexs[0].Position.x;
		aabb[0].y = aabb[1].y = meshes[0]->vertexs[0].Position.y;
		aabb[0].z = aabb[1].z = meshes[0]->vertexs[0].Position.z;

		for (int i = 0; i < meshes.size(); i++)
		{
			for (int j = 0; j < meshes[i]->vertexs.size(); j++) {
				if (meshes[i]->vertexs[j].Position.x < aabb[0].x) aabb[0].x = meshes[i]->vertexs[j].Position.x;
				if (meshes[i]->vertexs[j].Position.x > aabb[1].x) aabb[1].x = meshes[i]->vertexs[j].Position.x;
				if (meshes[i]->vertexs[j].Position.y < aabb[0].y) aabb[0].y = meshes[i]->vertexs[j].Position.y;
				if (meshes[i]->vertexs[j].Position.y > aabb[1].y) aabb[1].y = meshes[i]->vertexs[j].Position.y;
				if (meshes[i]->vertexs[j].Position.z < aabb[0].z) aabb[0].z = meshes[i]->vertexs[j].Position.z;
				if (meshes[i]->vertexs[j].Position.z > aabb[1].z) aabb[1].z = meshes[i]->vertexs[j].Position.z;
			}
		}

		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);
	}

	void Entity2::updateModelMatrix()
	{
			getTransform()->updateLocalModelMatrix();
		if (getParent() != NULL)
		{
			getTransform()->setLocalModel(getTransform()->getLocalModel());
			getTransform()->setWorldModel(getTransform()->getParentModel() * getTransform()->getLocalModel());
		}
		else
		{
			getTransform()->setWorldModel(getTransform()->getLocalModel());
		}
		setTransformations();
		
	}

	void Entity2::addBoundsToAABB(vector<glm::vec3> childAABB)
	{
		if (childAABB.size() < 1)
		{
			return;
		}
		else if (localAABB.size() < 1)
		{
			localAABB.clear();
			localAABB.push_back(childAABB[0]);
			localAABB.push_back(childAABB[1]);

			aabb.clear();
			aabb.push_back(childAABB[0]);
			aabb.push_back(childAABB[1]);

			return;
		}

		localAABB.clear();
		localAABB.push_back(aabb[0]);
		localAABB.push_back(aabb[1]);

		if (childAABB[0].x < localAABB[0].x) localAABB[0].x = childAABB[0].x;
		if (childAABB[1].x > localAABB[1].x) localAABB[1].x = childAABB[1].x;
		if (childAABB[0].y < localAABB[0].y) localAABB[0].y = childAABB[0].y;
		if (childAABB[1].y > localAABB[1].y) localAABB[1].y = childAABB[1].y;
		if (childAABB[0].z < localAABB[0].z) localAABB[0].z = childAABB[0].z;
		if (childAABB[1].z > localAABB[1].z) localAABB[1].z = childAABB[1].z;
	}

	vector<glm::vec3> Entity2::getLocalAABB()
	{
		return localAABB;
	}
	void Entity2::draw()
	{
		_renderer->UpdateMVP(getTransform()->getWorldModel());

		for (int i = 0; i < meshes.size(); i++)
			meshes[i]->Draw();
	}
}
