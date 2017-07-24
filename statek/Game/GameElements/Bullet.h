//
// Created by wysocki on 24/07/2017.
//

#ifndef STATEK_BULLET_H
#define STATEK_BULLET_H


#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IPhysicsable.h>
#include <Game/Interfaces/IRenderable.h>
#include <Game/Interfaces/ITickable.h>


class Bullet : public Actor, public IPhysicsable, public IRenderable, public ITickable {
public:
	static Bullet * createBullet(glm::vec3 position);
	
	Bullet(const btRigidBodyConstructionInfo &constructionInfo);
	
	
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetScale();
	virtual glm::vec3 GetRotation();
	
	virtual void ReactToCollision(IPhysicsable * other);
	
	virtual void Tick(float delta);
};


#endif //STATEK_BULLET_H
