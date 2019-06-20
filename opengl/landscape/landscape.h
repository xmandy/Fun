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

	bool Prepare();

	glm::vec3 GetVertexPosition(int X, int Z, const unsigned char *ImageData, int ImageWidth, int ImageHeight);

private:
	std::string HeigtMapImagePath;
	std::string VsPath;
	std::string PsPath;

	Shader GeoShader;

	int GeoHeight;
	BDT::Size GeoSize;

	std::vector<BDT::Vertex> Vertices;

};


#endif

