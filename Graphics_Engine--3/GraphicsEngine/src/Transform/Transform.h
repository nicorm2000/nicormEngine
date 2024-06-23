#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "GLM/glm.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "Exports/Exports.h"
#include "Component/Component.h"
using namespace glm;
using namespace std;
#define MAXCHILDREN 500;
namespace MikkaiEngine
{
	class GraficosEngine_API Transform :public Component
	{
	public:
		Transform();
		Transform(GameObject* gameObject);
		Transform(GameObject* gameObject, Entity2* ourEntity);
		~Transform();

		vec3 getposition()			        { return m_pos			; };
		vec3 getMatPos()					{ return localModel[3]  ; };
		vec3 geteulerAngles()		        { return m_eulerRot		; };
		vec3 getlocalScale()		        { return m_scale		; };
		
		mat4 getWorldModel()				{ return worldModel     ; };
		mat4 getLocalModel()				{ return localModel     ; };
		mat4 getParentModel()				{ return parentModel    ; };

		glm::vec3 getRight()	;
		glm::vec3 getUp()		;
		glm::vec3 getBackward() ;
		glm::vec3 getForward()  ;
		
		void setposition   (vec3 v) { m_pos      = v; };
		void seteulerAngles(vec3 v) { m_eulerRot = v; updateTransformRotation(); };
		void setRotX(float x);
		void setRotY(float y);
		void setRotZ(float z);

		void setlocalScale (vec3 v) { m_scale    = v;};

		void setForward(vec3 v);
		void setRight  (vec3 v);
		void setUp     (vec3 v);


		void setWorldModel (mat4 v) { worldModel  = v; }
		void setLocalModel (mat4 v) { localModel  = v; }
		void setParentModel(mat4 v) { parentModel = v; }


		void updateLocalModelMatrix();

		
	protected:
	private:

		vec3 m_pos;
		vec3 m_eulerRot;
		vec3 m_scale;

		glm::mat4 worldModel;
		glm::mat4 localModel;
		glm::mat4 parentModel;

		void updateTransformRotation();
		
	};
#pragma region OTHERS
	vec3 static QuatToVec(quat quat, vec3 vec);
	quat static EulerToQuat(vec3 euler);
#pragma endregion

}
#endif // !TRANSFORM_H
