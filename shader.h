#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<glad/glad.h>

enum class ShaderType: GLenum{
    VERTEX_SHADER = GL_VERTEX_SHADER,
    FRAGMENT_SHADER = GL_FRAGMENT_SHADER
};

// 获得shader编译时报错信息
static void GetCompileInfo(const ShaderType& type, unsigned int shaderId){
    char info[512];
    int success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderId, 512, NULL, info);
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
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(program, 512, NULL, info);
        std::cerr << "LINK Error: "<< info<<std::endl;
    }
}

class Shader{
public:
    Shader(): m_id(0){
    }
    Shader(const std::string& filename, ShaderType  type) :m_type(type){
        ReadSrc(filename);
        m_id = glCreateShader((GLenum)type);
        const char* ptr = m_source.c_str();
        glShaderSource(m_id, 1, &ptr, nullptr);
        glCompileShader(m_id);
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
    }

    operator unsigned int() const{
        return m_id;
    }

    const std::string GetSrc() const {return m_source;}

    unsigned int GetId() const{return m_id;}
protected:
    unsigned int m_id = 0;
    ShaderType m_type;
    std::string m_source;
};

class Program{
public:
    Program(const std::string& vertexFile, const std::string& fragmentFile)
        :m_vertexShader(vertexFile, ShaderType::VERTEX_SHADER), 
        m_fragmentShader(fragmentFile, ShaderType::FRAGMENT_SHADER){
        m_programId = glCreateProgram();
        glAttachShader(m_programId, m_vertexShader);
        glAttachShader(m_programId, m_fragmentShader);
        glLinkProgram(m_programId);
        GetLinkInfo(m_programId);
    }

    void Use() const{
        glUseProgram(m_programId);
    }

    void AttachShader(const Shader& shader) {
        glAttachShader(m_programId, shader);
    }
    operator unsigned int() const{
        return m_programId;
    }
protected:
    unsigned int m_programId;
    Shader m_vertexShader;
    Shader m_fragmentShader;
};