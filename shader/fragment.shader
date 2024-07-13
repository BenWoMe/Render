#version 330 core
in vec4 fragColor;
in vec2 fragCoord;
uniform vec4 uColor;
uniform sampler2D tex0;
out vec4 FragColor;
void main()
{
    FragColor = fragColor;
}