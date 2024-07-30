#include<iostream>
#include<string>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<format>
#define STB_IMAGE_IMPLEMENTATION
#include"shader.h"
#include"camera.h"
#include"model.hpp"
#include"gl_utility.hpp"
#include"vertex.hpp"

float g_deltaTime = 0.0f;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 
    45.0f, 800.0f/600.0f, 0.1f, 100.0f, "view");

glm::vec3 g_lightPos{0.0f, 0.0f, 2.0f};
glm::vec3 g_lightColor{1.0f, 1.0f, 1.0f};

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT) ){
        camera.MoveLeft(g_deltaTime);
    }

    if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.MoveFront(g_deltaTime);
    }

    if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.MoveBack(g_deltaTime);
    }

    if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        camera.MoveRight(g_deltaTime);
    }
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset){
    camera.Zoom(yoffset);
}

void CursorCallback(GLFWwindow* window, double xpos, double ypos){

}

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
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetCursorPosCallback(window, CursorCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Glad load failed."<<std::endl;
        return -1;
    }
    int nVertexAttribs;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nVertexAttribs);
    std::cout << "The max number of vertex attribs is "<< nVertexAttribs<<std::endl;

    glViewport(0,0, 800, 600);

float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
    //float vertices[] = {
        //// 3 pos + 3 color + 2 tex coord.
        //-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // 1
         //0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 2
         //0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, // 3
         //-0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 1.0f, // 4
        //-0.5f, -0.5f, 0.5f, 1.0f, 0.2f, 0.0f, 0.0f, 0.0f, // 5
         //0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.2f, 1.0f, 0.0f, // 6
         //0.5f, -0.5f, -0.5f, 0.2f, 0.0f, 1.0f, 0.5f, 1.0f, // 7
         //-0.5f, -0.5f, -0.5f, 0.9f, 0.9f, 0.5f, 0.5f, 1.0f // 8
    //};
    unsigned int index[] = {
        0, 1, 3, //上
        1, 2, 3,
        0, 1, 5, // 前
        0, 4, 5,
        2, 3, 7, // 后
        2, 6, 7,
        4, 5, 7, // 下
        5, 6, 7,
        0, 3, 4, // 左
        3, 4, 7,
        1, 2, 5, // 右
        2, 5, 6
    };


    Model nanosuit("../asset/nanosuit/nanosuit.obj");
    unsigned int VAO;
    GL_ERROR(glGenVertexArrays(1, &VAO));
    GL_ERROR(glBindVertexArray(VAO));

    unsigned int VEO;
    GL_ERROR(glGenBuffers(1, & VEO));
    GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO));
    GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW));

    unsigned int VBO;
    GL_ERROR(glGenBuffers(1, &VBO));
    GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GL_ERROR(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));


    unsigned int tex;
    GL_ERROR(glGenTextures(1, &tex));
    GL_ERROR(glActiveTexture(GL_TEXTURE0));
    GL_ERROR(glBindTexture(GL_TEXTURE_2D, tex));

    GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT));
    GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT));
    GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GL_ERROR(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

    int TEX_WIDTH, TEX_HEIGHT, channel;
    unsigned char* data = stbi_load("../asset/image.png", &TEX_WIDTH, &TEX_HEIGHT, &channel, 0);
    if(!data){
        throw std::runtime_error("texture data isn't exist.");
        return -1;
    }
    GL_ERROR(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_WIDTH, TEX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
    GL_ERROR(glGenerateMipmap(GL_TEXTURE_2D));
    stbi_image_free(data);
    

    unsigned int stride = 6 * sizeof(float);
    GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0));
    GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float))));
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6*sizeof(float)));
    GL_ERROR(glEnableVertexAttribArray(0));
    GL_ERROR(glEnableVertexAttribArray(1));
    //glEnableVertexAttribArray(2);



    
    Program program("../shader/vertex.shader", "../shader/fragment.shader");
    Program lightProgram("../shader/vertex.shader", "../shader/lightFragment.shader");
    Program marginProgram("../shader/vertex.shader", "../shader/singleColor.shader");

    GL_ERROR(glEnable(GL_DEPTH_TEST));
    GL_ERROR(glDepthFunc(GL_LESS));
    camera.AddProgram(program);
    camera.AddProgram(lightProgram);
    camera.AddProgram(marginProgram);

    glm::mat4 model(1.0f);

    program.SetMat4("model", glm::value_ptr(model));
    program.SetVec3("lightColor", glm::value_ptr(g_lightColor));



    auto current = glfwGetTime();
    while(!glfwWindowShouldClose(window)){
        GL_ERROR(glClearColor(0.2f, 0.3f, 0.4f, 1.0f)); // 清屏的范围和OpenGL的渲染范围不一样
        GL_ERROR(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));

        
        g_deltaTime = glfwGetTime() - current;
        current = glfwGetTime(); 

        g_lightPos = glm::vec3(5* sin(current), 1.0f, 5 *cos(current));
        // 画物体
        program.SetVec3("eyePos", glm::value_ptr(camera.GetPos()));
        program.SetVec3("lightPos", glm::value_ptr(g_lightPos));

        nanosuit.EnableMargin(marginProgram);
        nanosuit.Draw(program);// 标准模型

        program.Use();
        GL_ERROR(glBindVertexArray(VAO));
        GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));

        // 画光源
        lightProgram.SetMat4("model", glm::value_ptr(glm::translate(glm::mat4(1.0f), g_lightPos)));
        lightProgram.Use();
        GL_ERROR(glBindVertexArray(VAO));
        GL_ERROR(glDrawArrays(GL_TRIANGLES, 0, 36));


        GL_ERROR(glBindVertexArray(0));
        GL_ERROR(glfwPollEvents());
        GL_ERROR(glfwSwapBuffers(window));
    }

    program.Delete();
    lightProgram.Delete();
    glfwTerminate();
    return 0;
}