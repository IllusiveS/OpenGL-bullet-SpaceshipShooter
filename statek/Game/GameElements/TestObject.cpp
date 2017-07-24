//
// Created by wysocki on 22/07/2017.
//

#include <Graphics/Mesh.h>
#include "TestObject.h"
#include <Game.h>

glm::vec3 TestObject::GetPosition() {
	return glm::vec3(-5, 0, 0);
}

glm::vec3 TestObject::GetScale() {
	return glm::vec3(1.0, 1.0, 1.0);
}

glm::vec3 TestObject::GetRotation() {
	return glm::vec3();
}

TestObject::TestObject() {
	mesh = Game::GetGame()->renderer->retrieveMesh("rock");
}