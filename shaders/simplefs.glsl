#version 330 core
out vec4 FragColor;
uniform vec4 uColor;

in vec2 textCoor;

// Active Texture
uniform sampler2D ourTexture;
void main()
{
    FragColor = texture(ourTexture, textCoor);
}