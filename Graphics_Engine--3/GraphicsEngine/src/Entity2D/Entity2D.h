#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "../Exports/Exports.h"
#include "Entity2/Entity2.h"
#include "../Material/Material.h"
#include "../Entity/vertexs.h"
#include "Color/color.h"
namespace MikkaiEngine
{
	class GraficosEngine_API Entity2D : public Entity2 {
	public:
		Entity2D(Renderer* render);
		~Entity2D();

		void Draw();

		MikkaiEngine::Material* _material;

	protected:

		uint _VAO, _VBO, _EBO, tam, vertices;
		float* vertexs;

		void SetUniforms();
	private:
	};
}


#endif