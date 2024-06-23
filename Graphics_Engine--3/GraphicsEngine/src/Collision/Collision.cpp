//#include "collision.h"
//#include <math.h>
//
//	const float overlapSpeed = 0.25f;
//
//	Collision::Collision()
//	{
//
//	}
//
//	Collision::~Collision()
//	{
//
//	}
//
//	void Collision::CollisionUpdate(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (CheckCollisionRecRec(entity1, entity2))
//		{
//			std::cout << "Collision!" << std::endl;
//
//			Overlap(entity1, entity2);
//		}
//	}
//	bool Collision::CheckCollisionRecRec(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (entity2->_hasCollider && entity1->_hasCollider)
//		{
//			bool collisionX = entity1->getPos().x - (entity1->getScale().x / 2) + entity1->getScale().x >= entity2->getPos().x - (entity2->getScale().x / 2)
//				&& entity2->getPos().x - (entity2->getScale().x / 2) + entity2->getScale().x >= entity1->getPos().x - (entity1->getScale().x / 2);
//			// collision y-axis?
//			bool collisionY = entity1->getPos().y - (entity1->getScale().y / 2) + entity1->getScale().y >= entity2->getPos().y - (entity2->getScale().y / 2)
//				&& entity2->getPos().y - (entity2->getScale().y / 2) + entity2->getScale().y >= entity1->getPos().y - (entity1->getScale().y / 2);
//			// collision only if on both axes
//			return collisionX && collisionY;
//		}
//		return false;
//	}
//	bool Collision::CheckCollisionRecRecTile(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (entity2->_hasCollider && entity1->_hasCollider)
//		{
//			float px1= entity1->getPos().x;
//			float sx1= entity1->getScale().x;
//			float px2 = entity2->getPos().x;
//			float sx2 = entity2->getScale().x;
//			float py1 = entity1->getPos().y;
//			float sy1 = entity1->getScale().y;
//			float py2 = entity2->getPos().y;
//			float sy2 = entity2->getScale().y;
//			//el tema de truncar es porque el player no siempre esta centrado en la grid,
//			//para compensar esa diferencia. en X se trunca porque se redonde para abajo.
//			//en Y se redonde haceia arriba.
//			bool collisionX =
//				(
//					truncf(px1 - (sx1 / 2)) <= px2 + (sx2 / 2)
//					&&
//					truncf(px1 + (sx1 / 2)) >= px2- (sx2 / 2)
//				);
//
//			bool collisionY = 
//				(
//					ceilf(py1 - (sy1 / 2)) <= py2 + (sy2 / 2)
//					&&
//					ceilf(py1 + (sy1 / 2)) >= py2 - (sy2 / 2)
//				);
//
//			return collisionX && collisionY;
//		}
//		return false;
//	}
//	bool Collision::CheckCollisionRecRec2(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (entity2->_hasCollider && entity1->_hasCollider)
//		{
//			bool collisionX =
//				entity1->pivot.x - (entity1->colliderSize.x) + 
//				(entity1->colliderSize.x*2) >= entity2->pivot.x - (entity2->colliderSize.x) &&
//				entity2->pivot.x - (entity2->colliderSize.x) +
//				(entity2->colliderSize.x*2) >= entity1->pivot.x - (entity1->colliderSize.x);
//			// collision y-axis?
//			bool collisionY = 
//				entity1->pivot.y - (entity1->colliderSize.y) +
//				entity1->colliderSize.y * 2 >= entity2->pivot.y - (entity2->colliderSize.y) &&
//				entity2->pivot.y - (entity2->colliderSize.y) +
//				entity2->colliderSize.y * 2 >= entity1->pivot.y - (entity1->colliderSize.y);
//			// collision only if on both axes
//			return collisionX && collisionY;
//		}
//		return false;
//	}
//
//	bool Collision::CheckCollisionCircleCirclePivot(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (entity2->_hasCollider && entity1->_hasCollider)
//		{
//			//bool collisionX = entity1->pivot.x - (entity1->colliderSize.x) + entity1->getScale().x >= entity2->getPos().x - (entity2->getScale().x / 2)
//			//	&& entity2->getPos().x - (entity2->getScale().x / 2) + entity2->getScale().x >= entity1->getPos().x - (entity1->getScale().x / 2);
//			//// collision y-axis?
//			//bool collisionY = entity1->getPos().y - (entity1->getScale().y / 2) + entity1->getScale().y >= entity2->getPos().y - (entity2->getScale().y / 2)
//			//	&& entity2->getPos().y - (entity2->getScale().y / 2) + entity2->getScale().y >= entity1->getPos().y - (entity1->getScale().y / 2);
//			//// collision only if on both axes
//			////return collisionX && collisionY;
//
//			struct Circle1 { float r = 20; float x = 5; float y = 5; };
//			Circle1 c1 = {entity1->colliderSize.x,entity1->pivot.x,entity1->pivot.y};
//			struct circle2 { float r = 20; float x = 5; float y = 5; };
//			circle2 c2 = { entity2->colliderSize.x,entity2->pivot.x,entity2->pivot.y };
//
//
//			float dx = c1.x - c2.x;
//			float dy = c1.y - c2.y;
//			float distance = std::sqrt(dx * dx + dy * dy);
//			
//
//			if (distance < c1.r + c2.r) {
//				return true;
//			}
//		}
//		return false;
//	}
//
//	void Collision::Overlap(Entity2D* entity1, Entity2D* entity2) //Separa ambos objetos en el caso de existir overlap
//	{
//		if (entity2->_moveable)
//		{
//			glm::vec3 director = glm::vec3();
//			director = entity1->GetPivot() - entity2->GetPivot(); //Genero el vector director para saber hacia donde puedo 
//
//			do
//			{
//				director = glm::normalize(entity2->GetPivot() - entity1->GetPivot());
//				entity2->SetPos(entity2->GetPivot() + director * overlapSpeed);
//			} while (CheckCollisionRecRec(entity1, entity2));
//		}
//	}
//
//	void Collision::GoLastPos(Entity2D* entity1, Entity2D* entity2)
//	{
//		if (entity2->_moveable)
//			entity2->SetPos(entity2->getLastPos());
//		if (entity1->_moveable)
//			entity1->SetPos(entity1->getLastPos());
//		entity1->InitCollider();
//		entity2->InitCollider();
//		
//	}
//