//
// Created by wysocki on 22/07/2017.
//

#include <fstream>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Renderer.h"
#include <Game/Camera.h>
#include "Window.h"
#include "Mesh.h"
#include <Game/Interfaces/IRenderable.h>
#include <glfw-3.1.2/deps/linmath.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

Renderer::Renderer() {
    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );

    // Get a handle for our "MVP" uniform
    MatrixID = glGetUniformLocation(programID, "MVP");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");

    // Get a handle for our buffers
    vertexPosition_modelspaceID = glGetAttribLocation(programID, "vertexPosition_modelspace");
    vertexUVID = glGetAttribLocation(programID, "vertexUV");
    vertexNormal_modelspaceID = glGetAttribLocation(programID, "vertexNormal_modelspace");
}

Renderer::~Renderer() {
	for(std::pair<std::string, Mesh *> mesh : meshes) {
		delete mesh.second;
	}
	glDeleteProgram(programID);
}

GLuint Renderer::LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void Renderer::RenderAll(Window * window, Camera * camera) {
    glUseProgram(programID);
    
	camera->computeMatrices();
 
	glm::mat4 ProjectionMatrix = camera->getProjectionMatrix();
	glm::mat4 ViewMatrix = camera->getViewMatrix();
	
	glEnableVertexAttribArray(vertexNormal_modelspaceID);
	glEnableVertexAttribArray(vertexPosition_modelspaceID);
	glEnableVertexAttribArray(vertexUVID);
	
	for(IRenderable * rend : renders) {
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		
		glm::vec3 rotation = rend->GetRotation();
		glm::vec3 position = rend->GetPosition();
		glm::vec3 scale = rend->GetScale();
		
		glm::mat4 RotationMatrix = glm::eulerAngleYXZ(rotation.y, rotation.x, rotation.z);
		glm::mat4 TranslationMatrix = glm::translate(glm::mat4(), position); // A bit to the left
		glm::mat4 ScalingMatrix = glm::scale(glm::mat4(), scale);
		glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix;
		
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		
		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
		
		Mesh * mesh = rend->mesh;
		
		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(mesh->TextureID, 0);
		
		// 1rst attribute buffer : vertices
		
		glEnableVertexAttribArray(vertexPosition_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer);
		glVertexAttribPointer(
				vertexPosition_modelspaceID, // The attribute we want to configure
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
		);
		
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(vertexUVID);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer);
		glVertexAttribPointer(
				vertexUVID,                       // The attribute we want to configure
				2,                                // size : U+V => 2
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
		);
		
		// 3rd attribute buffer : normals
		glEnableVertexAttribArray(vertexNormal_modelspaceID);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbuffer);
		glVertexAttribPointer(
				vertexNormal_modelspaceID,        // The attribute we want to configure
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
		);
		
		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer);
		
		// Draw the triangles !
		glDrawElements(
				GL_TRIANGLES,      // mode
				mesh->indicesSize,    // count
				GL_UNSIGNED_SHORT,   // type
				(void*)0           // element array buffer offset
		);
		glDisableVertexAttribArray(vertexPosition_modelspaceID);
        glDisableVertexAttribArray(vertexUVID);
        glDisableVertexAttribArray(vertexNormal_modelspaceID);
	}
    
}

void Renderer::AddRenderable(IRenderable *render) {
	renders.push_back(render);
}

void Renderer::RemoveRenderable(IRenderable *render) {
	renders.remove(render);
}

void Renderer::LoadMesh(std::string name, std::string location) {
	Mesh * mesh = Mesh::readFromFile(location, programID);
	
	meshes.insert(std::pair<std::string, Mesh*>(name, mesh));
}

Mesh *Renderer::retrieveMesh(std::string name) {
	Mesh * foundMesh = nullptr;
	auto it = meshes.find(name);
	if (it != meshes.end())
		foundMesh = it->second;
	return foundMesh;
}

