#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "pointLight.h"
#include "../Camera/Camera.h"
#include "Camera2/Camera2.h"
namespace MikkaiEngine
{

	class GraficosEngine_API SpotLight : public PointLight
	{
	public:
		SpotLight(Renderer* render);
		void Init();
		void SetUniforms(std::string name) override;
		void UpdateLight() override;

		~SpotLight();
		void SetCamera(Camera* cam);
		void SetCamera(MikkaiEngine::Camera2* cam);
		void SetCutOff(float cutOff);
		void SetOuterCutOff(float outerCutOff);
		static int CuantitySpots;

	protected:

		Camera* _cam;
		MikkaiEngine::Camera2* _cam2;
		float cutOff;
		float outerCutOff;

		uint _uniformDirection;
		uint _uniformCutOff;
		uint _uniformOuterCutOff;
		static std::list<SpotLight*> SpotLists;
	};
}

#endif