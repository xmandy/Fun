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

		friend std::ostream& operator<<(std::ostream &os, Vertex &v)
		{
			return os << "(" << v.Position.x << ", " << v.Position.y << ", " << v.Position.z << ")" << std::endl;
		}
	};

	struct Size {
		int x;
		int y;
		Size(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		friend std::ostream& operator<<(std::ostream &os, Size &size)
		{
			return os << "Size: (" << size.x << " " << size.y << ")" << std::endl;
		}
	};
}


#endif