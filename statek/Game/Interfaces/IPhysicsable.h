//
// Created by wysocki on 23/07/2017.
//

#ifndef STATEK_IPHYSICSABLE_H
#define STATEK_IPHYSICSABLE_H


#include <string>
#include <BulletDynamics/Dynamics/btRigidBody.h>

class IPhysicsable : public btRigidBody {
public:
	IPhysicsable(btRigidBodyConstructionInfo constructionInfo);
	
	virtual ~IPhysicsable();

public:
	std::string type;
	virtual void ReactToCollision(IPhysicsable * other) = 0;
};


#endif //STATEK_IPHYSICSABLE_H
