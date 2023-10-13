#include <iostream>
#include "CollisionManager.h"

const float overlapSpeed = 0.01f;

CollisionManager::CollisionManager()
{
    entity2D = nullptr;
}

CollisionManager::~CollisionManager()
{
    if (entity2D != nullptr) {
        entity2D = nullptr;
        delete entity2D;
    }
}

void CollisionManager::CollisionUpdate(Entity2D* entity1, Entity2D* entity2)
{
	if (CheckCollision(entity1, entity2))
	{
		std::cout << "COLLISION" << std::endl;
		Overlap(entity1, entity2);
	}
}

bool CollisionManager::CheckCollision(Entity2D* entity1, Entity2D* entity2) // Rectangle - Rectangle
{
	if (entity2->HasCollider())
	{
		//                posicion x entity1                                     + escala x entity1      >= posicion x entity2 
		//				  && posicion x entity2                                     + escala x entity2      >= posicion x entity1
		bool collisionX = entity1->GetPosition().x - (entity1->GetScale().x / 2) + entity1->GetScale().x >= entity2->GetPosition().x - (entity2->GetScale().x / 2)
			&& entity2->GetPosition().x - (entity2->GetScale().x / 2) + entity2->GetScale().x >= entity1->GetPosition().x - (entity1->GetScale().x / 2);

		bool collisionY = entity1->GetPosition().y - (entity1->GetScale().y / 2) + entity1->GetScale().y >= entity2->GetPosition().y - (entity2->GetScale().y / 2)
			&& entity2->GetPosition().y - (entity2->GetScale().y / 2) + entity2->GetScale().y >= entity1->GetPosition().y - (entity1->GetScale().y / 2);

		return collisionX && collisionY; // The collision is true if it is on both axes
	}

	return false;
}

void CollisionManager::Overlap(Entity2D* entity1, Entity2D* entity2) //Separa ambos objetos en el caso de existir overlap
{
	if (entity2->IsMoveable())
	{
		do
		{
			glm::vec3 director = glm::normalize(entity2->GetPosition() - entity1->GetPosition()); //Genero el vector director para saber hacia donde puedo
			entity2->SetPosition((entity2->GetPosition() + director * overlapSpeed).x,
				(entity2->GetPosition() + director * overlapSpeed).y,
				(entity2->GetPosition() + director * overlapSpeed).z);
		} while (CheckCollision(entity1, entity2));
	}
	else
	{
		do
		{
			glm::vec3 director = glm::normalize(entity1->GetPosition() - entity2->GetPosition()); //Genero el vector director para saber hacia donde puedo
			entity1->SetPosition((entity1->GetPosition() + director * overlapSpeed).x,
				(entity1->GetPosition() + director * overlapSpeed).y,
				(entity1->GetPosition() + director * overlapSpeed).z);
		} while (CheckCollision(entity2, entity1));
	}
}