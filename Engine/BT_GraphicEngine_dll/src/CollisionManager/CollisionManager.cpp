#include "CollisionManager.h"

const float overlapSpeed = 0.35f;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::CollisionUpdate(Entity2D* entity1, Entity2D* entity2)
{
	if (CheckCollisionRecRec(entity1, entity2))
	{
		cout << "Collision!" << endl;
		Overlap(entity1, entity2);
	}
}

bool CollisionManager::CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2)
{
	if (entity2->HasCollider())
	{
		// bool collisionX = entity1->GetPosX() + entity1->GetScaleX() >= entity2->GetPosX() && entity2->GetPosX() + entity2->GetScaleX() >= entity1->GetPosX();
		bool collisionX = entity1->GetPositionX() - (entity1->GetScaleX() / 2) + entity1->GetScaleX() >= entity2->GetPositionX() - (entity2->GetScaleX() / 2)
			&& entity2->GetPositionX() - (entity2->GetScaleX() / 2) + entity2->GetScaleX() >= entity1->GetPositionX() - (entity1->GetScaleX() / 2);
		// collision y-axis?
		bool collisionY = entity1->GetPositionY() - (entity1->GetScaleY() / 2) + entity1->GetScaleY() >= entity2->GetPositionY() - (entity2->GetScaleY() / 2)
			&& entity2->GetPositionY() - (entity2->GetScaleY() / 2) + entity2->GetScaleY() >= entity1->GetPositionY() - (entity1->GetScaleY() / 2);
		// collision only if on both axes
		return collisionX && collisionY;
	}

	return false;
}

void CollisionManager::Overlap(Entity2D* entity1, Entity2D* entity2) // Separa ambos objetos en el caso de existir overlap
{
	if (entity2->IsMoveable())
	{
		do
		{
			glm::vec3 director = glm::normalize(entity2->GetPosition() - entity1->GetPosition()); // Genero el vector director para saber hacia donde puedo
			entity2->SetPosition(entity2->GetPosition() + director * overlapSpeed);
		} while (CheckCollisionRecRec(entity1, entity2));
	}
}