#version 330 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoord;
out vec3 norm;
out vec3 fragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main(){
    gl_Position = projection * view * model* vec4(Pos, 1.0f);
    fragPos = vec3(model*vec4(Pos, 1.0f));
    norm = normalize(mat3(transpose(inverse(model))) * aNormal);
}