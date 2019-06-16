#include "landscape.h"
#include "SOIL.h"

Landscape::Landscape(std::string& imagePath, BDT::Size &size, int height, std::string& vsPath, std::string& psPath):
	heigtMapImagePath(imagePath), geoSize(size), geoHeight(height), vsPath(vsPath), psPath(psPath),
	geoShader(vsPath, psPath)
{

}

bool Landscape::Prepare()
{
	// step 1: load height map image.
	int width;
	int height;
	int channels;
	unsigned char *image = SOIL_load_image(heigtMapImagePath.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	std::cout << width << " " << height << " " << " " << channels << std::endl;

	for (int row = 0; row < geoSize.x, ++row)
	{
		for (int col = 0; col < geoSize.y, ++col)
		{
		
		}
	}



	return true;


}

