//
// Created by wysocki on 22/07/2017.
//

#include <stdexcept>
#include <tiny_obj_loader.h>
#include <glm/vec2.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Mesh.h"

Mesh *Mesh::readFromFile(std::string name, GLuint programId) {
    Mesh * meshToRead = new Mesh();

    readMesh(name + ".obj", meshToRead);
    readTexture(name + "Tex", meshToRead, programId);
    
    return meshToRead;
}

void Mesh::readMesh(std::string name, Mesh *mesh) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;
    
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, name.c_str())) {
        throw std::runtime_error(err);
    }
    
    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            
            glm::vec3 temp_vertice = {};
            glm::vec2 temp_uv = {};
            glm::vec3 temp_norm = {};
            glm::vec3 temp_color = {};
            
            temp_vertice = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
            };
            
            temp_uv = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
            };
            
            temp_norm = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2]
            };
            
            temp_color = { 1.0f, 1.0f, 1.0f };
            
            temp_vertices.push_back(temp_vertice);
            temp_uvs.push_back(temp_uv);
            temp_normals.push_back(temp_norm);
        }
    }
    
    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(temp_vertices, temp_uvs, temp_normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
    
    glGenBuffers(1, &(mesh->vertexbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &(mesh->uvbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &(mesh->normalbuffer));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &(mesh->elementbuffer));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);
	mesh->indicesSize = indices.size();
}

void Mesh::indexVBO(
        std::vector<glm::vec3> & in_vertices,
        std::vector<glm::vec2> & in_uvs,
        std::vector<glm::vec3> & in_normals,

        std::vector<unsigned short> & out_indices,
        std::vector<glm::vec3> & out_vertices,
        std::vector<glm::vec2> & out_uvs,
        std::vector<glm::vec3> & out_normals
){
    std::map<PackedVertex,unsigned short> VertexToOutIndex;

    // For each input vertex
    for ( unsigned int i=0; i<in_vertices.size(); i++ ){

        PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};


        // Try to find a similar vertex in out_XXXX
        unsigned short index;
        bool found = getSimilarVertexIndex_fast( packed, VertexToOutIndex, index);

        if ( found ){ // A similar vertex is already in the VBO, use it instead !
            out_indices.push_back( index );
        }else{ // If not, it needs to be added in the output data.
            out_vertices.push_back( in_vertices[i]);
            out_uvs     .push_back( in_uvs[i]);
            out_normals .push_back( in_normals[i]);
            unsigned short newindex = (unsigned short)out_vertices.size() - 1;
            out_indices .push_back( newindex );
            VertexToOutIndex[ packed ] = newindex;
        }
    }
}

bool Mesh::getSimilarVertexIndex_fast(
        PackedVertex & packed,
        std::map<PackedVertex,unsigned short> & VertexToOutIndex,
        unsigned short & result
){
    std::map<PackedVertex,unsigned short>::iterator it = VertexToOutIndex.find(packed);
    if ( it == VertexToOutIndex.end() ){
        return false;
    }else{
        result = it->second;
        return true;
    }
}



void Mesh::readTexture(std::string name, Mesh *mesh, GLuint programId) {
    int texWidth, texHeight, texChannels;
    stbi_uc * image = nullptr;
    stbi_uc * imagebasic = stbi_load((name).c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc * imagetga = stbi_load((name+".tga").c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    stbi_uc * imagejpeg = stbi_load((name+".jpg").c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
    
    if (imagebasic) {
        image = imagebasic;
    }
	if(imagetga) {
		image = imagetga;
	}
	if(imagejpeg) {
		image = imagejpeg;
	}
    
    if (!image) {
        throw std::runtime_error("failed to load texture " + name + " !");
    }
    
    if(image == nullptr)
        throw(std::string("Failed to load texture"));
    
    glGenTextures(1, &(mesh->Texture));
    
    glBindTexture(GL_TEXTURE_2D, mesh->Texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    if(texChannels == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    else if(texChannels == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    
    glBindTexture(GL_TEXTURE_2D, 0);
	mesh->TextureID = glGetUniformLocation(programId, "myTextureSampler");
    stbi_image_free(image);
}

void Mesh::Draw(glm::vec3 pos, glm::vec3 sca, glm::vec3 rot) {

}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &normalbuffer);
	glDeleteBuffers(1, &elementbuffer);
	glDeleteTextures(1, &Texture);
}
