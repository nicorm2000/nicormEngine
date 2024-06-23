#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Object/Object.h"
#include "Transform/Transform.h"
namespace MikkaiEngine
{
	class GraficosEngine_API GameObject : protected Object
	{
	public:
		GameObject();
		GameObject(Entity2* ourEntity);
		~GameObject();
		int getLayer() { return layer; };
		bool getactive() { return active; };
		string getTag() { return tag; };
		bool getisStatic() { return isStatic; };
		string getName() { return _name; };

		void setLayer(int v) { layer = v; };
		void setActive(bool v) 
		{
			active = v;
		};
		void setTag(string v) { tag = v; };
		void setisStatic(bool v) { isStatic = v; };
		void setName(string v) { _name = v; };

		Transform* getTransform() { return transform; }
	protected:
		Transform& getPrTransform() { return *transform; }
		bool isShoweable;
	private:
		Transform* transform;
		int layer;
		bool active;
		bool showeable;
		string tag;
		bool isStatic;
		string _name;

	};

}

#endif // !GAMEOBJECT_H
