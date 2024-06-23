#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H

#include "light.h"
namespace MikkaiEngine
{
	class GraficosEngine_API DirectionLight : public Light
	{
	public:
		DirectionLight(Renderer* render);
		void Init();
		void SetUniforms(std::string name) override;
		void UpdateLight() override;

		~DirectionLight();
		void SetDirection(glm::vec3 direction);
		glm::vec3 GetDirection();

		static std::list<DirectionLight*> DirectionLightLists;
	protected:
		glm::vec3 direction;

		uint _uniformDirection;
	private:
		friend class MyImGui;
	};

}



#endif // !LIGHT_H