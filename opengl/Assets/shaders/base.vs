#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;


out vec3 outNormal;
out vec2 TexCoord;

layout (std140) uniform WolrdMatrix
{
	mat4 view;
	mat4 projection;
};
uniform mat4 model;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	outNormal = normal;
	TexCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}
