//
// Created by wysocki on 24/07/2017.
//

#include "Bullet.h"
#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <Game.h>


Bullet::Bullet(const btRigidBody::btRigidBodyConstructionInfo &constructionInfo) : IPhysicsable(constructionInfo) {

}

Bullet *Bullet::createBullet(glm::vec3 position) {
	btDefaultMotionState* asteroidMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(position.x, position.y, position.z)));
	btCollisionShape* asteroidShape = new btSphereShape(0.2f);
	
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	asteroidShape->calculateLocalInertia(mass, fallInertia);
	
	btRigidBody::btRigidBodyConstructionInfo asteroidRigidbodyCI(mass, asteroidMotionState, asteroidShape, fallInertia);
	Bullet* bullet = new Bullet(asteroidRigidbodyCI);
	
	bullet->setRestitution(1.0);
	
	bullet->setDamping(0, 0);
	
	bullet->setCollisionFlags(bullet->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	bullet->activate(true);
	bullet->applyCentralImpulse(btVector3(0, 0, -10));
	bullet->mesh = Game::GetGame()->renderer->retrieveMesh("bullet");
	bullet->type = "bullet";
	return bullet;
}

glm::vec3 Bullet::GetPosition() {
	btTransform trans;
	getMotionState()->getWorldTransform(trans);
	btVector3 vec = trans.getOrigin();
	//printf("asteroid pos: %f, %f, %f \n", vec.x(), vec.y(), vec.z());
	return glm::vec3(vec.x(), vec.y(), vec.z());
}

glm::vec3 Bullet::GetScale() {
	return glm::vec3(0.05, 0.05, 0.05);
}

glm::vec3 Bullet::GetRotation() {
	return glm::vec3();
}

void Bullet::ReactToCollision(IPhysicsable *other) {
	
}

void Bullet::Tick(float delta) {
	glm::vec3 pos = GetPosition();
	if (pos.z < -11){
		Destroy();
	}
}
