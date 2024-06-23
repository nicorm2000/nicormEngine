#ifndef SPRITE_H
#define SPRITE_H
#include "Texture/MyTexture.h"
#include "Exports/Exports.h"
#include "Entity2D/Entity2D.h"
#include "Renderer/Renderer.h"
#include <GLM/glm.hpp>
#include <vector>
#include "Animation/Animation.h"
#include "Atlas/Atlas.h"
#include "Entity/vertexs.h"

namespace MikkaiEngine
{
	enum class ORDER
	{
		RIGHTtoLEFT,
		UPtoDOWN
	};

	enum class SPRITE_TYPE
	{
		QUAD,
		CUBE
	};
	class GraficosEngine_API Sprite : public Entity2D {
	private:
		SPRITE_TYPE type;
		uint _UVB;

		MikkaiEngine::Texture* baseTexture;

		uint _uniformBaseTexture;

		void SetTexture(MikkaiEngine::Texture* texture, MikkaiEngine::TEXTURE_TYPE type);

		void SetUniforms();

		//__________________________
		bool _settedAnimsValues;

		//std::vector<Animation*> anim;
	public:
		Sprite(Renderer* render);
		~Sprite();

		void Init(SPRITE_TYPE type);
		//void Update(float timer);
		void LoadTexture(const char* path, bool invertImage, MikkaiEngine::TEXTURE_TYPE type);
		void Draw();
		void DeInit();
		//void SetTexture(MyTexture* texture);
		//void AddAnimation(Atlas atlas, float speed);
		//void AddAnimation(int rows, int cols, float duration);
		//void ChangeAnimation(int index);
		//void SetTextureCoordinates(Frame f);
	};
}
#endif
