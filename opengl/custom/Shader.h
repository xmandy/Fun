#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

class Shader
{
	public:
		GLuint Program;
        GLuint CreateShader(const std::string path, GLuint shader_type);
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath=NULL);
		Shader(const std::string &vertexPath, const std::string &fragPath, const std::string geoPath="");
		Shader();
		void Use();

		std::string VsPath;
		std::string PsPath;
		std::string GeoPath;

		void SetInt(const std::string &Name, int Value)
		{
			glUniform1i(glGetUniformLocation(Program, Name.c_str()), Value);
		}

		void SetMat4(const std::string &Name, const glm::mat4 &mat)
		{
			glUniformMatrix4fv(glGetUniformLocation(Program, Name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
		}

private:
	void Initialize(const std::string vertexPath, const std::string fragmentPath, const std::string geometryPath = "");
};
#endif
