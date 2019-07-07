#ifndef LINE_H__
#define LINE_H__
#include "BasicDataTypes.h"
#include "gl/glew.h"
#include "Shader.h"
#include <vector>

class Line {
public:
	Line(std::vector<BDT::LineVertex> &Vertices, std::string &VsPath, std::string &PsPath, GLenum LineMode);

	bool SetUp();

	void Draw(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);


private:
	std::vector<BDT::LineVertex> VertexVector;
	GLenum LineDrawMode;
	Shader LineShader;

	GLuint LineVAO;
	GLuint LineVBO;

};

#endif
