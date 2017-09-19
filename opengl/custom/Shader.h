#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
	public:
		GLuint Program;
        GLuint CreateShader(const GLchar* path, GLuint shader_type);
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath=NULL);
		void Use();
};
#endif
