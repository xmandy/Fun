#version 330 core

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
// this is just to reuse the deferred rendering fbo
layout (location = 2) out vec3 gAlbedo;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

void main()
{
    gPosition = FragPos;

    gNormal = normalize(Normal);

    gAlbedo = vec3(0.95);

}