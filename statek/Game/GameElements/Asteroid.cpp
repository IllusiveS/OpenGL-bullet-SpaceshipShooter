//
// Created by wysocki on 22/07/2017.
//

#include <LinearMath/btDefaultMotionState.h>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <Graphics/Mesh.h>
#include <time.h>
#include <BulletCollision/CollisionShapes/btSphereShape.h>
#include <Game.h>
#include "Asteroid.h"

Asteroid * Asteroid::CreateAsteroid(glm::vec3 pos) {
	float a = rand() % 180;
	float b = rand() % 180;
	float c = rand() % 180;
	
	btDefaultMotionState* asteroidMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pos.x, pos.y, pos.z)));
	btCollisionShape* asteroidShape = new btSphereShape(1);
	
	btScalar mass = 1;
	btVector3 fallInertia(0, 0, 0);
	asteroidShape->calculateLocalInertia(mass, fallInertia);
	
	btRigidBody::btRigidBodyConstructionInfo asteroidRigidbodyCI(mass, asteroidMotionState, asteroidShape, fallInertia);
	Asteroid* asteroid = new Asteroid(asteroidRigidbodyCI, asteroidMotionState, asteroidShape);
	
	asteroid->setRestitution(1.0);
	
	/* generate secret number between 1 and 10: */
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)) - 0.5f;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1)) + 1.5f;
	
	asteroid->setDamping(0, 0);
	
	asteroid->rot = glm::vec3(a, b, c);
	
	asteroid->activate(true);
	asteroid->applyCentralImpulse(btVector3(x, 0, y));
	asteroid->SetMesh(Game::GetGame()->renderer->retrieveMesh("rock"));
	asteroid->type = "asteroid";
	return asteroid;
}

Asteroid::Asteroid(btRigidBody::btRigidBodyConstructionInfo CI, btDefaultMotionState* state, btCollisionShape* collShape) : IPhysicsable(CI) {

}

Asteroid::~Asteroid() {

}

void Asteroid::ReactToCollision(IPhysicsable *other) {

}

glm::vec3 Asteroid::GetPosition() {
	btTransform trans;
	getMotionState()->getWorldTransform(trans);
	btVector3 vec = trans.getOrigin();
	//printf("asteroid pos: %f, %f, %f \n", vec.x(), vec.y(), vec.z());
	return glm::vec3(vec.x(), vec.y(), vec.z());
}

glm::vec3 Asteroid::GetScale() {
	return glm::vec3(1.0, 1.0, 1.0);
}

glm::vec3 Asteroid::GetRotation() {
	return glm::vec3();
}

void Asteroid::SetMesh(Mesh *mesh) {
	this->mesh = mesh;
}
