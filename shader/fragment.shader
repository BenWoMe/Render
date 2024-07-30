#version 330 core
in vec3 fragPos; // 片段位置
in vec3 norm; // 法向量
uniform vec3 eyePos; // 摄像机位置
uniform vec3 lightPos; // 光源位置
uniform vec3 lightColor; // 光源颜色
out vec4 FragColor; // 输出的片段颜色


void main()
{
    vec3 fragColor = vec3(1.0f, 0.5f, 0.3f);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir ,norm), 0.0f);

    vec3 refDir = normalize(reflect(-lightDir, norm));
    float jm = max(dot(refDir, normalize(eyePos - fragPos)),0);
    float inspect = pow(jm, 32);

    float amb = 0.1f;
    FragColor = vec4((amb + diff + inspect) * lightColor * fragColor, 1.0f);
    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0f);

}