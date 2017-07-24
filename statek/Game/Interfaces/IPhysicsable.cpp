//
// Created by wysocki on 24/07/2017.
//

#include "IPhysicsable.h"
#include <Game.h>

IPhysicsable::IPhysicsable(btRigidBodyConstructionInfo constructionInfo) : btRigidBody(constructionInfo) {
		Game::GetGame()->SubscribePhysics(this);
}

IPhysicsable::~IPhysicsable() {
	Game::GetGame()->UnSubscribePhysics(this);
}