//
// Created by wysocki on 24/07/2017.
//

#ifndef STATEK_BULLET_H
#define STATEK_BULLET_H


#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IPhysicsable.h>
#include <Game/Interfaces/IRenderable.h>

class Bullet : public Actor, public IPhysicsable, public IRenderable {
public:
	Bullet(const btRigidBodyConstructionInfo &constructionInfo);
	
};


#endif //STATEK_BULLET_H
