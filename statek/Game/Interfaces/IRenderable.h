//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_IRENDERABLE_H
#define STATEK_IRENDERABLE_H


#include <glm/vec3.hpp>
#include <GL/glew.h>

class Mesh;

class IRenderable {
public:
	IRenderable();
	virtual ~IRenderable();
	
	Mesh * mesh;
	
	virtual glm::vec3 GetPosition() = 0;
	virtual glm::vec3 GetScale() = 0;
	virtual glm::vec3 GetRotation() = 0;
};


#endif //STATEK_IRENDERABLE_H
