#version 330 core
out vec4 FragColor;
uniform float uMoveX;
void main()
{
    FragColor = vec4(0.0f+abs(uMoveX)/2, 1.0f-abs(uMoveX), 0.0f+abs(uMoveX), 1.0f);
}