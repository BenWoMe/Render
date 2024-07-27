#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<glad/glad.h>
#include"gl_utility.hpp"
enum class ShaderType: GLenum{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

// 获得shader编译时报错信息
static void GetCompileInfo(const ShaderType& type, unsigned int shaderId){
    char info[512];
    int success;
    GL_ERROR(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success));
    if(!success){
        GL_ERROR(glGetShaderInfoLog(shaderId, 512, NULL, info));
        if(type == ShaderType::VERTEX_SHADER){
            std::cerr << "VERTEX SHADER : "<< info<<std::endl;
        }else{
            std::cerr << "FRAGMENT SHADER : "<<info<<std::endl;
        }
    }
    
}

// 获得shader链接时报错信息
static void GetLinkInfo(unsigned int program){
    int success;
    char info[512];
    GL_ERROR(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if(!success){
        GL_ERROR(glGetProgramInfoLog(program, 512, NULL, info));
        std::cerr << "LINK Error: "<< info<<std::endl;
    }
}

class Shader{
public:
    Shader(): m_id(0){
    }
    Shader(const std::string& filename, ShaderType  type) :m_type(type){
        ReadSrc(filename);
        GL_ERROR(m_id = glCreateShader((GLenum)type));
        const char* ptr = m_source.c_str();
        GL_ERROR(glShaderSource(m_id, 1, &ptr, nullptr));
        GL_ERROR(glCompileShader(m_id));
        GetCompileInfo(type, m_id);
    }
    bool ReadSrc(const std::string& filename){
        std::fstream fs;
        fs.open(filename);
        if(!fs) {
            std::cerr << filename << " doesn't exist."<<std::endl;
            return -1;
        }
        while(!fs.eof()){
            std::string tmp;
            std::getline(fs, tmp);
            m_source += tmp + "\n";
        }
        return true;
    }

    operator unsigned int() const{
        return m_id;
    }

    const std::string GetSrc() const {return m_source;}

    unsigned int GetId() const{return m_id;}
    ~Shader() {
        GL_ERROR(glDeleteShader(m_id));
    }
protected:
    unsigned int m_id = 0;
    ShaderType m_type;
    std::string m_source;
};

class Program{
public:
    Program(): m_programId(0){
    }
    Program(const std::string& vertexFile, const std::string& fragmentFile)
        :m_vertexShader(vertexFile, ShaderType::VERTEX_SHADER), 
        m_fragmentShader(fragmentFile, ShaderType::FRAGMENT_SHADER){
        GL_ERROR(m_programId = glCreateProgram());
        GL_ERROR(glAttachShader(m_programId, m_vertexShader));
        GL_ERROR(glAttachShader(m_programId, m_fragmentShader));
        GL_ERROR(glLinkProgram(m_programId));
        GL_ERROR(GetLinkInfo(m_programId));
    }


    void Use() const{
        GL_ERROR(glUseProgram(m_programId));
    }
    void UnUse() const{
        GL_ERROR(glUseProgram(0));
    }

    void AttachShader(const Shader& shader) {
        Use();
        GL_ERROR(glAttachShader(m_programId, shader));
        UnUse();
    }
    operator unsigned int() const{
        return m_programId;
    }

    void SetMat4(const std::string& name, const float* value) const{
        Use();
        unsigned int location;
        GL_ERROR(location = glGetUniformLocation(m_programId, name.c_str()));
        GL_ERROR(glUniformMatrix4fv(location, 1, GL_FALSE, value));
        UnUse();
    }

    void SetVec3(const std::string& name, const float* value) const{
        Use();
        unsigned int location;
        GL_ERROR(location = glGetUniformLocation(m_programId, name.c_str()));
        GL_ERROR(glUniform3f(location, value[0], value[1], value[2]));
        UnUse();
    }

    void Delete() const{
        GL_ERROR(glDeleteProgram(m_programId));
    }

    // 如果出现拷贝怎么办?
    ~Program(){
        GL_ERROR(glUseProgram(0));
    }

protected:
    unsigned int m_programId;
    Shader m_vertexShader;
    Shader m_fragmentShader;
};