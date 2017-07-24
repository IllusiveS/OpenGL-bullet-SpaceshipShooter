//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_CAMERA_H
#define STATEK_CAMERA_H

#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec3.hpp>
#include <Graphics/Window.h>

class Camera {
public:
	Camera(Window * window);

private:
	GLFWwindow * window;
	
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	glm::vec3 position;
	
	float horizontalAngle;
	float verticalAngle;
	float fov;
	
	float mouseSpeed;
	
public:
	void computeMatrices();
	
	glm::mat4 getViewMatrix(){
		return ViewMatrix;
	}
	glm::mat4 getProjectionMatrix(){
		return ProjectionMatrix;
	}
};


#endif //STATEK_CAMERA_H
