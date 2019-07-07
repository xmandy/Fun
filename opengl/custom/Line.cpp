#include "Line.h"
#include "gtc/type_ptr.hpp"

Line::Line(std::vector<BDT::LineVertex> &Vertices, std::string &VsPath, std::string &PsPath, GLenum LineMode):
VertexVector(Vertices),
LineShader(VsPath, PsPath),
LineDrawMode(LineMode)
{
}

bool Line::SetUp()
{
	glGenVertexArrays(1, &LineVAO);
	glGenBuffers(1, &LineVBO);

	glBindVertexArray(LineVAO);
	glBindBuffer(GL_ARRAY_BUFFER, LineVBO);
	glBufferData(GL_ARRAY_BUFFER, VertexVector.size() * sizeof(BDT::LineVertex), &VertexVector[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::LineVertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(BDT::LineVertex),
		(void*)offsetof(BDT::LineVertex, Color));

	glBindVertexArray(0);
	return true;

}


void Line::Draw(glm::mat4 &Model, glm::mat4 &View, glm::mat4 &Projection)
{
	LineShader.Use();

	GLuint ProjLoc = glGetUniformLocation(LineShader.Program, "projection");
	GLuint ViewLoc = glGetUniformLocation(LineShader.Program, "view");
	GLuint modelLoc = glGetUniformLocation(LineShader.Program, "model");

	glUniformMatrix4fv(ProjLoc, 1, false, glm::value_ptr(Projection));
	glUniformMatrix4fv(ViewLoc, 1, false, glm::value_ptr(View));
	glUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(Model));

	glBindVertexArray(LineVAO);
	glDrawArrays(LineDrawMode, 0, VertexVector.size());
	glBindVertexArray(0);
}
