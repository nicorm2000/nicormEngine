#include "Entity3D.h"

namespace MikkaiEngine
{
	std::list<Entity3D*> Entity3D::entitys3dList;
	Entity3D::Entity3D(Renderer* render, std::string path)
	{
		model = new Model(render);
	#if IMPORTER
		Importer2 inp;
		model->SetBaseNode(inp.LoadModel(render, path));
	#endif // IMPORTER
		entitys3dList.push_back(this);
	}
	Entity3D::~Entity3D()
	{
		entitys3dList.remove(this);
	}
}
