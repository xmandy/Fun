#ifndef BASEDATATYPES_H__
#define BASEDATATYPES_H__
#include "glm.hpp"
#include "gl/glew.h"
#include <iostream>

namespace BDT{

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


		Vertex(glm::vec3 &Pos)
		{
			Position = Pos;
			Normal = glm::vec3(0, 0, 1);
			TexCoords = glm::vec2(0, 0);
		}

		friend std::ostream& operator<<(std::ostream &os, Vertex &v)
		{
			return os << "(" << v.Position.x << ", " << v.Position.y << ", " << v.Position.z << ")" << std::endl;
		}
	};

	struct Size {
		int X;
		int Y;
		Size(int _X, int _Y)
		{
			X = _X;
			Y = _Y;
		}
		friend std::ostream& operator<<(std::ostream &Os, Size &ThisSize)
		{
			return Os << "Size: (" << ThisSize.X << " " << ThisSize.Y << ")" << std::endl;
		}
	};
}


#endif