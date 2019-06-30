#ifndef LANDSCALE_H_
#define LANDSCALE_H_
#include <string>
#include <vector>
#include "GL/glew.h"
#include "glm.hpp"
#include "Shader.h"
#include "BasicDataTypes.h"

class Landscape
{
public:
	Landscape(std::string& ImagePath, BDT::Size &Size, int Height, std::string& VsPath, std::string& PsPath);

	bool SetUp();

	glm::vec3 GetVertexPosition(int X, int Z, const unsigned char *ImageData, int ImageWidth, int ImageHeight);
	void Draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);

	Shader GeoShader;

private:
	std::string HeigtMapImagePath;
	std::string VsPath;
	std::string PsPath;


	int GeoHeight;
	BDT::Size GeoSize;

	std::vector<BDT::Vertex> Vertices;

	// OpenGL variables
	GLuint mVAO, mVBO, mEBO;


};


#endif

