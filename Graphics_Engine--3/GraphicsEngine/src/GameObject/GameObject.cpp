#include "GameObject.h"

MikkaiEngine::GameObject::GameObject():Object()
{
	active = true; 
	layer = 0;
	transform =new Transform(this);
	tag = ""; 
	AddDescription("-> ||GameObject|| ");
}
MikkaiEngine::GameObject::GameObject(Entity2* ourEntity)
{
	active = true;
	layer = 0;
	transform = new Transform(this,ourEntity);
	tag = "";
	AddDescription("-> ||GameObject|| ");
}
MikkaiEngine::GameObject::~GameObject()
{
	if (transform != NULL)
	{
		delete transform;
		transform = NULL;
	}
}

