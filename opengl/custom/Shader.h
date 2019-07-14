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
        GLuint CreateShader(const std::string path, GLuint shader_type);
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath=NULL);
		Shader(const std::string &vertexPath, const std::string &fragPath, const std::string geoPath="");
		Shader();
		void Use();

		std::string VsPath;
		std::string PsPath;
		std::string GeoPath;
private:
	void Initialize(const std::string vertexPath, const std::string fragmentPath, const std::string geometryPath = "");
};
#endif
