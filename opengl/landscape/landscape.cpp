#include "landscape.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "SOIL.h"

Landscape::Landscape(std::string& ImagePath, BDT::Size &Size, int height, std::string& VsPath, std::string& PsPath):
	HeigtMapImagePath(ImagePath), GeoSize(Size), GeoHeight(height), VsPath(VsPath), PsPath(PsPath),
	GeoShader(VsPath, PsPath)
{
	//std::cout << "111111111111111111 " << &GeoShader << " " << GeoShader.Program << " aa " << GeoShader.VsPath << std::endl;

}

glm::vec3 Landscape::GetVertexPosition(int X, int Z, const unsigned char *ImageData, int ImageWidth, int ImageHeight)
{
	int Offset = int(X / float(GeoSize.X) * ImageWidth) * 3 + \
		int(Z / float(GeoSize.Y) * ImageHeight) *ImageWidth * 3;
	//std::cout << X << " " << Z << " " << Offset <<" " << ImageWidth * ImageHeight * 3 << std::endl;
	if (Offset >= ImageWidth*ImageHeight*3)
		std::cout << X << " " << Z << " " << Offset << " " << ImageWidth * ImageHeight * 3 << std::endl;

	//std::cout << int(ImageData[Offset] / 255.0 * GeoHeight) << std::endl;
	return glm::vec3(X, ImageData[Offset] / 255.0 * 5, Z);
	//return glm::vec3(X, 0, Z);

}

bool Landscape::SetUp()
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


	for (int Row = 0; Row < GeoSize.X - 1; ++Row)
	{

		for (int Col = 0; Col < GeoSize.Y - 1; ++Col)
		{
			float XStart = Row;
			float ZStart = Col;
			glm::vec3 pos0 = GetVertexPosition(XStart, ZStart, ImageData, Width, Height);
			glm::vec3 pos1 = GetVertexPosition(XStart, ZStart + 1, ImageData, Width, Height);
			glm::vec3 pos2 = GetVertexPosition(XStart + 1, ZStart, ImageData, Width, Height);
			glm::vec3 pos3 = GetVertexPosition(XStart + 1, ZStart + 1, ImageData, Width, Height);

			Vertices.push_back(BDT::Vertex(pos0));
			Vertices.push_back(BDT::Vertex(pos1));
			Vertices.push_back(BDT::Vertex(pos2));

			Vertices.push_back(BDT::Vertex(pos2));
			Vertices.push_back(BDT::Vertex(pos1));
			Vertices.push_back(BDT::Vertex(pos3));
		}
	}

	SOIL_free_image_data(ImageData);
	//Vertices.clear();
	//Vertices.push_back(BDT::Vertex(glm::vec3(1, 1, 0.0)));
	//Vertices.push_back(BDT::Vertex(glm::vec3(1, -1, 0.0)));
	//Vertices.push_back(BDT::Vertex(glm::vec3(-1, 1, 0.0)));

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(BDT::Vertex), &Vertices[0], GL_STATIC_DRAW);

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)0);

	// normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)offsetof(BDT::Vertex, Normal));
	
	// tex corrds
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)offsetof(BDT::Vertex, TexCoords));

	glBindVertexArray(0);

	return true;

}

void Landscape::Draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
{
	GeoShader.Use();

	GLuint modelLoc = glGetUniformLocation(GeoShader.Program, "model");
	GLuint viewLoc = glGetUniformLocation(GeoShader.Program, "view");
	GLuint projlLoc = glGetUniformLocation(GeoShader.Program, "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projlLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, Vertices.size());
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


