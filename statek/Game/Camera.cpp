//
// Created by wysocki on 22/07/2017.
//

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"


#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;


Camera::Camera(Window * window) : position(glm::vec3(0, 20, 0)),
	horizontalAngle(3.14f), verticalAngle(0.0f), fov(45.0f), window(window->window), mouseSpeed(1.0f)
{

}

void Camera::computeMatrices(){
	
	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();
	
	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	double xpos = 0, ypos = 0;
	glfwGetCursorPos(window, &xpos, &ypos);
	
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);
	
	horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
	
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );
	
	float FoV = fov;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
			position,           // Camera is here
			position + glm::vec3(0, -1, 0), // and looks here : at the same position, plus "direction"
			glm::vec3(0, 0, -1)                  // Head is up (set to 0,-1,0 to look upside-down)
	);
	
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}