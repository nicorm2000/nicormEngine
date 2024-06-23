#include "Component.h"
namespace MikkaiEngine
{
#pragma region PRIVATE_VARIABLES
#pragma endregion
#pragma region CONSTRUCTORS
#pragma endregion
#pragma region GETTERS
#pragma endregion
#pragma region SETTERS
#pragma endregion
#pragma region OPERATORS
#pragma endregion
	Component::Component(Transform* transform)
	{
		this->transform = transform;
		this->gameObject = nullptr;
		tag = "default";
		AddDescription("-> ||Component|| ");
	}
	Component::Component(Transform* transform, GameObject* gameObject)
	{
		this->transform = transform;
		this->gameObject = gameObject;
		tag = "default";
		AddDescription("-> ||Component|| ");
	}
	Component::Component(Transform* transform, GameObject* gameObject, Entity2* ourEntity)
	{
		this->transform = transform;
		this->gameObject = gameObject;
		this->ourEntity = ourEntity;
		tag = "default";
		AddDescription("-> ||Component|| ");
	}
	Component::~Component()
	{
	}
}

