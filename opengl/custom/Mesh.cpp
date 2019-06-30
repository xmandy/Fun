#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture> &textures)
{
	mTest = false;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
    setupMesh();
}

Mesh::Mesh()
{
	mTest = true;

	GLint SideCount = 36;
	const float PI = 3.1415926535897932384626433832795;
	float HalfHight = 0.5f;

	for (int i = 0; i <= SideCount; ++i)
	{
		// gen top mesh
		GLfloat angle = i * PI * 2 / SideCount;
		//BDT::Vertex vertex(cos(angle), HalfHight, sin(angle), 0.0f, 1.0f, 0.0f,
		//	(cos(angle) + 1) / 2.0, (sin(angle) / 2.0));
		//TopVertices.push_back(vertex);

		// gen middle rectangle
		BDT::Vertex vertexDown(cos(angle), -HalfHight, sin(angle), cos(angle), 0, sin(angle),
			i / (float)SideCount, 0.0f);
		BDT::Vertex vertexUp(cos(angle), HalfHight, sin(angle), cos(angle), 0, sin(angle),
			i / (float)SideCount, 1.0f);

		//std::cout << vertexDown << vertexUp;
		mSideVertices.push_back(vertexDown);
		mSideVertices.push_back(vertexUp);

		// gen bottom mesh
		//angle = -angle;
		//BDT::Vertex bvertex(cos(angle), -HalfHight, sin(angle), 0.0f, 0.0f, 1.0f,
		//	(cos(angle) + 1) / 2.0, (sin(angle) / 2.0));
		//BottomVertices.push_back(bvertex);

	}

	glGenVertexArrays(1, &mTestVAO);
	glGenBuffers(1, &mTestVBO);

	glBindVertexArray(mTestVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, mTestVBO);
	glBufferData(GL_ARRAY_BUFFER, mSideVertices.size() * sizeof(BDT::Vertex), &mSideVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)offsetof(BDT::Vertex, Normal));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(BDT::Vertex), (void*)offsetof(BDT::Vertex, TexCoords));
	glBindVertexArray(0);


}

void Mesh::DrawTest(Shader &shader)
{
	glBindVertexArray(mTestVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, mSideVertices.size());
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// vertex shader attribute

	// position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

void Mesh::Draw(Shader &shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream ss;
        std::string num;
        std::string name = textures[i].tex_type;
		if (name == "texture_diffuse")
			ss << diffuseNr++;
		else if (name == "texture_specular")
			ss << specularNr++;
		num = ss.str();
//		glUniform1i(glGetUniformLocation(shader.Program, ("material." + name + num).c_str()), i);
		glUniform1i(glGetUniformLocation(shader.Program, (name + num).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
