#pragma once
#include<glad/glad.h>
#include<string>
#include<iostream>
#include<format>


[[clang::optnone]] static bool GLGetError(const char* file, int line){
    GLenum errorCode;
    bool ret = false;
    while((errorCode = glGetError()) != GL_NO_ERROR){
        std::string error;
        switch(errorCode){
            case GL_INVALID_ENUM: error = "Invalid Enum"; break;
            case GL_INVALID_VALUE: error = "Invalid Value"; break;
            case GL_INVALID_OPERATION: error = "Invalid Operation"; break;
            case GL_STACK_OVERFLOW: error = "Overflow"; break;
            case GL_STACK_UNDERFLOW: error = "Underflow"; break;
            case GL_OUT_OF_MEMORY: error = " Out of Memory"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "Invalid FrameBuffer Operation"; break;
        }
        std::cerr << std::format("error : {} , filepath : {} >> line : {}", error, file, line)<<std::endl;
        ret = true;
    }
    return ret;
}

#ifdef _Debug
    #ifdef MSVC
        #define debugbreak __debugbreak
    #elif defined(__clang__)
        #define debugbreak __builtin_debugtrap
    #endif

    #define GL_ERROR(func) \
        do{                \
            func;          \
            if(GLGetError(__FILE__, __LINE__)) {debugbreak();}  \
        }while(0)

#else
    #define GL_ERROR(func) func
#endif

