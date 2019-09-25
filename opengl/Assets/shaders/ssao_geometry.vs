#version 330 core
layout (location = 0) in vec3 InPosition;
layout (location = 1) in vec3 InNormal;
layout (location = 2) in vec2 InTexCoord;


out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform bool invertedNormals;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec4 viewPos = view * model * vec4(InPosition, 1.0);
    FragPos = viewPos.xyz;
    TexCoords = InTexCoord;

    mat3 normalMatrix = transpose(inverse(mat3(view*model)));
    Normal = normalMatrix * (invertedNormals ? -InNormal: InNormal);

    gl_Position = projection * viewPos;

}