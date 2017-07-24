//
// Created by wysocki on 24/07/2017.
//

#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <Game.h>
#include <BulletDynamics/ConstraintSolver/btGeneric6DofConstraint.h>
#include "PlayerShip.h"

PlayerShip::PlayerShip(const btRigidBody::btRigidBodyConstructionInfo &constructionInfo)
		: IPhysicsable(constructionInfo), speed(50.0f), limit(11.5f) {
	
}

PlayerShip *PlayerShip::CreateShip() {
	btDefaultMotionState* asteroidMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 8)));
	btCollisionShape* asteroidShape = new btSphereShape(0.05);
	
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	asteroidShape->calculateLocalInertia(mass, fallInertia);
	
	btRigidBody::btRigidBodyConstructionInfo asteroidRigidbodyCI(mass, asteroidMotionState, asteroidShape, fallInertia);
	PlayerShip* ship = new PlayerShip(asteroidRigidbodyCI);
	
	//ship->setRestitution(1.0);
	
	/* generate secret number between 1 and 10: */
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)) - 0.5f;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)) + 1.5f;
	
	ship->setDamping(0.99, 0.99);
	
	ship->activate(true);
	//ship->applyCentralImpulse(btVector3(x, 0, y));
	ship->mesh = Game::GetGame()->renderer->retrieveMesh("ship");
	//ship->setCollisionFlags(ship->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	return ship;
}

void PlayerShip::ReactToCollision(IPhysicsable *other) {

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
	if(GetPosition().x > limit) {
		activate(true);
		applyCentralImpulse(btVector3(delta * speed * -1 * 2, 0, 0));
	}
	if(GetPosition().x < -limit) {
		activate(true);
		applyCentralImpulse(btVector3(delta * speed * 1 * 2, 0, 0));
	}
}
