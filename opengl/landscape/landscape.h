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
	Landscape(std::string& imagePath, BDT::Size &size, int height, std::string& vsPath, std::string& psPath);

	bool Prepare();

private:
	std::string heigtMapImagePath;
	std::string vsPath;
	std::string psPath;

	Shader geoShader;

	int geoHeight;
	BDT::Size geoSize;

	std::vector<BDT::Vertex> mVertices;

};


#endif

