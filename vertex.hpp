#pragma once
#include<iostream>
#include<glad/glad.h>
#include<type_traits>
#include<unordered_map>
#include<algorithm>

extern std::unordered_map<int, std::size_t> g_typeSize;

struct Attribute{
    Attribute() : count(0), type(GL_FLOAT){};
    Attribute(int cnt, int tp = GL_FLOAT): count(cnt), type(tp){}
    operator int() const {return type;}
    int Count() const {return count;}
    int Type() const {return type;}
    std::size_t ElementSize() const { return g_typeSize[type];}
    std::size_t Size() const{return count * g_typeSize.at(type);}

    int count;
    int type;
};

class VertexBuffer{
public:
    VertexBuffer(){
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    } 

    void BufferData(void* data, int sz, GLenum usage = GL_STATIC_DRAW){
        glBufferData(GL_ARRAY_BUFFER, 1, data, usage);
    }

    ~VertexBuffer(){
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
protected:
    unsigned int m_id;
};

class ElementBuffer{
public:
    ElementBuffer(){
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    } 

    void BufferData(void* data, int sz, GLenum usage = GL_STATIC_DRAW){
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 1, data, usage);
    }

    ~ElementBuffer(){
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
protected:
    unsigned int m_id;
};
class VertexArray{
public:
    VertexArray(){
        glGenVertexArrays(1, &m_id);
        glBindVertexArray(m_id);
    }

    void AddAtrrib(const Attribute& attrib){
        m_attributes.push_back(attrib);
    }

    void  BufferData(void* data, int sz, GLenum usage =  GL_STATIC_DRAW){
        m_vertexBuffer.BufferData(data, sz, usage);
    }

    void ElementBufferData(void* data, int sz, GLenum usage = GL_STATIC_DRAW){
        m_ElemeentBuffer.BufferData(data, sz, usage);
    }
    void AddAttribs(const std::vector<Attribute>& attrib){
        m_attributes = attrib;
    }

    void EnableAttrib() const{
        int stride = GetAtrribSize();
        int offset = 0;
        for(int i = 0; i < m_attributes.size(); ++i){
            glVertexAttribPointer(i, m_attributes[i].Count(), m_attributes[i].Type(), GL_FALSE, stride, (void*)offset);
            offset += m_attributes[i].Size();
            glEnableVertexAttribArray(i);
        }
    }
     
    int GetAtrribSize() const{
        int sz = 0;
        for(auto& item : m_attributes){
            sz += item.Size();
        }
        return sz;
    }

    void Delete(){
    }

    ~VertexArray(){
        glBindVertexArray(0);
    }
private:
    unsigned int m_id;

    std::vector<Attribute> m_attributes;
    VertexBuffer m_vertexBuffer;
    ElementBuffer m_ElemeentBuffer;
};