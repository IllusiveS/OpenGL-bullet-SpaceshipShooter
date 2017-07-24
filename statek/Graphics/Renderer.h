//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_RENDERER_H
#define STATEK_RENDERER_H

class Window;
class Camera;
class Mesh;

#include <Graphics/OpenGLHeaders.h>
#include <list>
#include <map>

class IRenderable;

class Renderer {
public:
    Renderer();
    ~Renderer();

    GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
    
	void LoadMesh(std::string name, std::string location);
	Mesh * retrieveMesh(std::string name);
	
    void RenderAll(Window * window, Camera * camera);
	
	void AddRenderable(IRenderable * render);
	void RemoveRenderable(IRenderable * render);
	
private:
    // Create and compile our GLSL program from the shaders
    GLuint programID;

    // Get a handle for our "MVP" uniform
    GLuint MatrixID;
    GLuint ViewMatrixID;
    GLuint ModelMatrixID;

    // Get a handle for our buffers
    GLuint vertexPosition_modelspaceID;
    GLuint vertexUVID;
    GLuint vertexNormal_modelspaceID;

	std::list<IRenderable *> renders;
	std::map<std::string, Mesh*> meshes;
};


#endif //STATEK_RENDERER_H
