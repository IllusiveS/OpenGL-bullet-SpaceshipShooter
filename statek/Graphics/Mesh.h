//
// Created by wysocki on 22/07/2017.
//

#ifndef STATEK_MESH_H
#define STATEK_MESH_H


#include <string>
#include <Graphics/OpenGLHeaders.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <cstring>
#include <map>
#include <vector>



class Mesh {
public:
    static Mesh * readFromFile(std::string name, GLuint programId);
	
private:
    static void readMesh(std::string name, Mesh * mesh);
    static void readTexture(std::string name, Mesh * mesh, GLuint programId);
	
public:
    void Draw(glm::vec3 pos, glm::vec3 sca, glm::vec3 rot);

	~Mesh();
	
public:
    
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint normalbuffer;
    GLuint elementbuffer;
    
    // Load the texture
    GLuint Texture;

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID;
	
	int indicesSize;

private:
    struct PackedVertex{
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
        bool operator<(const PackedVertex that) const{
            return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
        };
    };

    static bool getSimilarVertexIndex_fast(
            PackedVertex & packed,
            std::map<PackedVertex,unsigned short> & VertexToOutIndex,
            unsigned short & result
    );

    static void indexVBO(
            std::vector<glm::vec3> & in_vertices,
            std::vector<glm::vec2> & in_uvs,
            std::vector<glm::vec3> & in_normals,

            std::vector<unsigned short> & out_indices,
            std::vector<glm::vec3> & out_vertices,
            std::vector<glm::vec2> & out_uvs,
            std::vector<glm::vec3> & out_normals
    );
};


#endif //STATEK_MESH_H
