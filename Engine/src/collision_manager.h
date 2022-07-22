#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H
#include "export.h"
#include "entity2D.h"
#include "sprite.h"
#include "vec3.hpp"
#include "iostream"
using namespace std;
namespace Engine {

	enum ENGINE_API collisionPos {
		none,
		topCollision,
		rightCollision,
		leftCollision,
		bottomCollision
	};

	class ENGINE_API CollisionManager {
	private:
		Entity2D* _entity;
		collisionPos PartialCollision(Entity2D* entity, Entity2D* otherEntity);
	public:
		CollisionManager();
		~CollisionManager();
		bool CheckTrigger(Entity2D* entity1, Entity2D* entity2);
		bool CheckCollision(Entity2D* entity1, Entity2D* entity2, float speedEntity1);
		bool ColisionWithSprite(Entity2D* entity, Sprite* sprite);
	};
}

#endif