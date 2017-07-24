//
// Created by wysocki on 22/07/2017.
//


#include "PhysicsEngine.h"
#include <LinearMath/btScalar.h>
#include <LinearMath/btVector3.h>
#include <btBulletDynamicsCommon.h>

#include <BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h>
#include <BulletCollision/CollisionDispatch/btCollisionConfiguration.h>
#include <BulletCollision/BroadphaseCollision/btBroadphaseInterface.h>
#include <BulletCollision/CollisionDispatch/btCollisionDispatcher.h>
#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <Game/Interfaces/IPhysicsable.h>

PhysicsEngine::PhysicsEngine() {
	bt_collision_configuration = new btDefaultCollisionConfiguration();
	bt_dispatcher = new btCollisionDispatcher(bt_collision_configuration);
	
	btScalar sscene_size = (btScalar) scene_size;
	btVector3 worldAabbMin(-sscene_size, -sscene_size, -sscene_size);
	btVector3 worldAabbMax(sscene_size, sscene_size, sscene_size);
//This is one type of broadphase, bullet has others that might be faster depending on the application
	bt_broadphase = new btDbvtBroadphase(); // true for disabling raycast accelerator
	solver = new btSequentialImpulseConstraintSolver();
	bt_collision_world = new btDiscreteDynamicsWorld(bt_dispatcher, bt_broadphase, solver, bt_collision_configuration);
	bt_collision_world->setGravity(btVector3(0, 0, 0));
}

PhysicsEngine::~PhysicsEngine() {
	delete bt_collision_world;
	delete solver;
	delete bt_collision_configuration;
	delete bt_dispatcher;
	delete bt_broadphase;
}

void PhysicsEngine::ProcessPhysics(float timePassed) {
	bt_collision_world->stepSimulation(1.f/60.f,10);
	bt_collision_world->performDiscreteCollisionDetection();
	int numManifolds = bt_collision_world->getDispatcher()->getNumManifolds();
	
	for (int i = 0; i < numManifolds; i++) {
		btPersistentManifold* contactManifold = bt_collision_world->getDispatcher()->getManifoldByIndexInternal(i);
		const IPhysicsable* obA = dynamic_cast<const IPhysicsable*>(contactManifold->getBody0());
		const IPhysicsable* obB = dynamic_cast<const IPhysicsable*>(contactManifold->getBody1());
		
		IPhysicsable* first = const_cast<IPhysicsable *>(obA);
		IPhysicsable* second = const_cast<IPhysicsable *>(obB);
		
		contactManifold->refreshContactPoints(obA->getWorldTransform(), obB->getWorldTransform());
		
		first->ReactToCollision(second);
		second->ReactToCollision(first);
	}
}

void PhysicsEngine::AddObject(IPhysicsable *body) {
	bt_collision_world->addRigidBody(body);
}

void PhysicsEngine::RemoveObject(IPhysicsable *body) {
	bt_collision_world->removeRigidBody(body);
}




