#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<format>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include"shader.h"


int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
    if(window == nullptr){
        glfwTerminate();
        std::cerr << "GLFWwindow is nullptr."<<std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Glad load failed."<<std::endl;
        return -1;
    }
    int nVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nVertexAttribs);
    std::cout << "The max number of vertex attribs is "<< nVertexAttribs<<std::endl;

    glViewport(50,50, 400, 300);


    float vertices[] = {
        // 3 pos + 3 color + 2 tex coord.
        -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,
         0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };
    unsigned int index[] = {
        0, 1, 2, // 第一个三角形
        0, 1, 3 // 第二个三角形
    };


    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VEO;
    glGenBuffers(1, & VEO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    unsigned int tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int TEX_WIDTH, TEX_HEIGHT, channel;
    unsigned char* data = stbi_load("asset/image.png", &TEX_WIDTH, &TEX_HEIGHT, &channel, 0);
    if(!data){
        throw std::runtime_error("texture data isn't exist.");
        return -1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_WIDTH, TEX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    
    Program program("shader/vertex.shader", "shader/fragment.shader");
    program.Use();

    unsigned int stride = 8 * sizeof(float);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glUseProgram(program);
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f); // 清屏的范围和OpenGL的渲染范围不一样
        glClear(GL_COLOR_BUFFER_BIT);

        float t = glfwGetTime();
        float green = 0.5*(sin(t)+1);
        GLint location = glGetUniformLocation(program, "uColor");
        glUniform4f(location, 1.0f, green ,0.5f, 1.0f);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6,  GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}