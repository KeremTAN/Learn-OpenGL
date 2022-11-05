#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat3 uMtxTransform;
void main()
{
    gl_Position = vec4(uMtxTransform*aPos, 1.0);
}