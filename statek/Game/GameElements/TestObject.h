//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_TESTOBJECT_H
#define STATEK_TESTOBJECT_H


#include <Game/Interfaces/Actor.h>
#include <Game/Interfaces/IRenderable.h>

class Mesh;

class TestObject : public Actor, public IRenderable {
public:
	TestObject();
	
	virtual glm::vec3 GetPosition() override;
	virtual glm::vec3 GetScale() override;
	virtual glm::vec3 GetRotation() override;
};


#endif //STATEK_TESTOBJECT_H
