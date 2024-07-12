#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
out vec4 fragColor;
out vec2 fragCoord;
void main(){
    gl_Position = vec4(Pos, 1.0f);
    fragColor = vec4(color, 1.0f);
    fragCoord = texCoord;
}