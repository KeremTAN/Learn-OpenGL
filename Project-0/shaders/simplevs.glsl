#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;

uniform mat3 uMtxTransform;
out vec2 textCoor = aTexture; 
void main()
{
    gl_Position = vec4(uMtxTransform*aPos, 1.0);
}