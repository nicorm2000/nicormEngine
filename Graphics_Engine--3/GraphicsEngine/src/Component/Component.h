#ifndef COMPONENT_H
#define COMPONENT_H
#include "Object/Object.h"
namespace MikkaiEngine
{
class Transform;
class GameObject;
class Entity2;
	class GraficosEngine_API Component : public Object
	{
    public:
        Component() { tag = "default"; AddDescription("-> ||Component|| ");};
        Component(Transform* transform);
        Component(Transform* transform, GameObject* gameObject);
        Component(Transform* transform, GameObject* gameObject, Entity2* ourEntity);
		~Component();
        Transform* getTransform() { return transform; };
        GameObject* getGameObject() { return gameObject; };
        Entity2* getEntity() { return ourEntity; };
    protected:
            
       
        void setTag(string v) { tag = v; };
        string getTag() { return tag; };
	private:
            //
            // Resumen:
            //     The tag of this game object.
        string tag;
        //
            // Resumen:
            //     The game object this component is attached to. A component is always attached
            //     to a game object.
        // public GameObject gameObject{ get; }

        Transform* transform;
        GameObject* gameObject;
        Entity2* ourEntity;
	};
}
#endif // !COMPONENT_H
