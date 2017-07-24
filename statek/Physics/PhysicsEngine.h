//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_PHYSICSENGINE_H
#define STATEK_PHYSICSENGINE_H

class btCollisionConfiguration;
class btSequentialImpulseConstraintSolver;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btDiscreteDynamicsWorld;
class btRigidBody;
class IPhysicsable;

class PhysicsEngine {
public:
	PhysicsEngine();
	~PhysicsEngine();
	
	void ProcessPhysics(float timePassed);
	void AddObject(IPhysicsable * body);
	void RemoveObject(IPhysicsable * body);
protected:
	btCollisionConfiguration * bt_collision_configuration;
	btSequentialImpulseConstraintSolver * solver;
	btCollisionDispatcher * bt_dispatcher;
	btBroadphaseInterface * bt_broadphase;
	btDiscreteDynamicsWorld * bt_collision_world;
	
	double scene_size = 500;
	unsigned int max_objects = 16000;
};


#endif //STATEK_PHYSICSENGINE_H
