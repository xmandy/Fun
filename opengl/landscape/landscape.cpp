#include "landscape.h"
#include "SOIL.h"

Landscape::Landscape(std::string& ImagePath, BDT::Size &Size, int height, std::string& VsPath, std::string& PsPath):
	HeigtMapImagePath(ImagePath), GeoSize(Size), GeoHeight(height), VsPath(VsPath), PsPath(PsPath),
	GeoShader(VsPath, PsPath)
{

}

glm::vec3 Landscape::GetVertexPosition(int X, int Z, const unsigned char *ImageData, int ImageWidth, int ImageHeight)
{
	int Offset = int(X / float(GeoSize.X) * ImageWidth) * 3 + \
		int(Z / float(GeoSize.Y) * ImageHeight) *ImageWidth * 3;
	//std::cout << X << " " << Z << " " << Offset <<" " << ImageWidth * ImageHeight * 3 << std::endl;
	if (Offset >= ImageWidth*ImageHeight*3)
		std::cout << X << " " << Z << " " << Offset << " " << ImageWidth * ImageHeight * 3 << std::endl;



	//std::cout << int(ImageData[Offset]) << std::endl;
	return glm::vec3(X, ImageData[Offset], Z);

}

bool Landscape::Prepare()
{
	// step 1: load height map Image.
	int Width;
	int Height;
	int Channels;
	unsigned char *ImageData = SOIL_load_image(HeigtMapImagePath.c_str(), &Width, &Height, &Channels, SOIL_LOAD_RGB);
	std::cout << Width << " " << Height << " " << " " << Channels << " " << std::endl;
	std::cout << ImageData[0] << "," << ImageData[1] << "," << ImageData[2] << std::endl;
	std::cout << ImageData[Width*Height*3 - 1] << "," << ImageData[Width*Height*3 - 2] << "," << ImageData[Width*Height*3 -3] << std::endl;
	//std::cout << int(ImageData[Width*Height*3]) <<std::endl;


	for (int Row = 0; Row < GeoSize.X; ++Row)
	{

		for (int Col = 0; Col < GeoSize.Y; ++Col)
		{
			float XStart = Row;
			float ZStart = Col;
			GetVertexPosition(XStart, ZStart, ImageData, Width, Height);

		
		}
	}

	SOIL_free_image_data(ImageData);

	return true;

}

