#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>

#include <string>
#include <vector>
#include "Shader.h"
#include <iostream>
#include <sstream>
#include <glm.hpp>
#include "BasicDataTypes.h"



#ifndef VERTEX_STRUCT
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	Vertex(GLfloat PosX, GLfloat PosY, GLfloat PosZ,
		GLfloat NormalX, GLfloat NormalY, GLfloat NormalZ,
		GLfloat TexX, GLfloat TexY)
	{
		Position.x = PosX;
		Position.y = PosY;
		Position.z = PosZ;
		Normal.x = NormalX;
		Normal.y = NormalY;
		Normal.z = NormalZ;
		TexCoords.x = TexX;
		TexCoords.y = TexY;
	}

	Vertex()
	{
		Position = glm::vec3(0, 0, 0);
		Normal = glm::vec3(0, 0, 1);
		TexCoords = glm::vec2(0, 0);
	}


	friend std::ostream& operator<<(std::ostream &os, Vertex &v)
	{
		return os << "(" << v.Position.x << ", " << v.Position.y << ", " << v.Position.z << ")" << std::endl;
	}
};
#define VERTEX_STRUCT
#endif

struct Texture 
{
	GLuint id;
	std::string tex_type;
    std::string path;
};

class Mesh {
public:
	/* Mesh Data*/
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures);

	Mesh();
	void Draw(Shader &shader);
	void DrawTest(Shader &shader);



private:
	void setupMesh();
	GLuint mVAO, mVBO, mEBO;

	bool mTest;
	GLuint mTestVAO, mTestVBO;
	std::vector<BDT::Vertex> mSideVertices;
};


#endif
