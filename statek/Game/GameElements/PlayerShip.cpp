//
// Created by wysocki on 24/07/2017.
//

#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <Game.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include <chrono>
#include "PlayerShip.h"
#include "Bullet.h"

PlayerShip::PlayerShip(const btRigidBody::btRigidBodyConstructionInfo &constructionInfo)
		: IPhysicsable(constructionInfo), speed(50.0f), limit(11.5f), prevSpawnTime(0), timeBetweenSpawns(500){
	currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

PlayerShip *PlayerShip::CreateShip() {
	btDefaultMotionState* asteroidMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 8)));
	btCollisionShape* asteroidShape = new btSphereShape(1);
	
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	asteroidShape->calculateLocalInertia(mass, fallInertia);
	
	btRigidBody::btRigidBodyConstructionInfo asteroidRigidbodyCI(mass, asteroidMotionState, asteroidShape, fallInertia);
	PlayerShip* ship = new PlayerShip(asteroidRigidbodyCI);
	
	ship->setDamping(0.99, 0.99);
	
	ship->activate(true);
	//ship->applyCentralImpulse(btVector3(x, 0, y));
	ship->mesh = Game::GetGame()->renderer->retrieveMesh("ship");
	//ship->setCollisionFlags(ship->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	ship->type = "ship";
	return ship;
}

void PlayerShip::ReactToCollision(IPhysicsable *other) {
	if(other->type == "asteroid"){
		Game::GetGame()->RestartScene();
	}
}

glm::vec3 PlayerShip::GetPosition() {
	btTransform trans;
	getMotionState()->getWorldTransform(trans);
	btVector3 vec = trans.getOrigin();
	//printf("asteroid pos: %f, %f, %f \n", vec.x(), vec.y(), vec.z());
	return glm::vec3(vec.x(), vec.y(), vec.z());
}

glm::vec3 PlayerShip::GetScale() {
	return glm::vec3(0.05, 0.05, 0.05);
}

glm::vec3 PlayerShip::GetRotation() {
	return glm::vec3();
}

void PlayerShip::Tick(float delta) {
	currentTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
	
	if (glfwGetKey( Game::GetGame()->window->window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		if(GetPosition().x < limit){
			activate(true);
			applyCentralImpulse(btVector3(delta * speed * 1, 0, 0));
		}
	}
	if (glfwGetKey( Game::GetGame()->window->window, GLFW_KEY_LEFT ) == GLFW_PRESS) {
		if(GetPosition().x > -limit) {
			activate(true);
			applyCentralImpulse(btVector3(delta * speed * -1, 0, 0));
		}
	}
	if (glfwGetKey( Game::GetGame()->window->window, GLFW_KEY_SPACE ) == GLFW_PRESS) {
		
		if(currentTime > prevSpawnTime){
			Bullet::createBullet(GetPosition());
			prevSpawnTime = currentTime + (int)timeBetweenSpawns;
		}
		
	}
	if(GetPosition().x > limit) {
		activate(true);
		applyCentralImpulse(btVector3(delta * speed * -1 * 2, 0, 0));
	}
	if(GetPosition().x < -limit) {
		activate(true);
		applyCentralImpulse(btVector3(delta * speed * 1 * 2, 0, 0));
	}
}
