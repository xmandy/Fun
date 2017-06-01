#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <string>
#include <vector>
#include "Shader.h"
#include <iostream>
#include <sstream>



struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

};

struct Texture 
{
	GLuint id;
	string tex_type;
	//aiString path;
};

class Mesh {
public:
	/* Mesh Data*/
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	Mesh(vector<Vertex> &vertices, vector<unsigned int> &indices, vector<Texture> &textures);
	void Draw(Shader &shader);

private:
	void setupMesh();
	GLuint mVAO, mVBO, mEBO,
};


#endif