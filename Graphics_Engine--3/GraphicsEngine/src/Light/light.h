#ifndef LIGHT_H
#define LIGHT_H

#include "Exports/Exports.h"
#include "GLM/ext/matrix_transform.hpp"
#include "Entity2/Entity2.h"
namespace MikkaiEngine
{
	class GraficosEngine_API Light : public Entity2
	{
	public:
		Light(Renderer* render);

		void virtual SetUniforms(std::string name);
		void virtual UpdateLight();

		~Light();


		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);

		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

		static std::list<Light*> LightsLists;
	protected:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		uint _uniformAmbient;
		uint _uniformDiffuse;
		uint _uniformSpecular;
	private:
		friend class MyImGui;
	};
}

#endif