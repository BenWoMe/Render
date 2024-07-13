#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;
out vec4 fragColor;
out vec2 fragCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
    gl_Position = projection * view * model* vec4(Pos, 1.0f);
    fragColor = vec4(color, 1.0f);
    fragCoord = texCoord;
}