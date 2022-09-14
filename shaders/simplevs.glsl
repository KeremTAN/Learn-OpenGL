#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 uMove;
void main()
{
    gl_Position = vec4(aPos+uMove, 1.0);
}