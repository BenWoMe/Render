#pragma once



class VertexBuffer{
public:

protected:
    unsigned int m_id;
};

class VertexBuffer{
public:
    VertexBuffer(const VertexBuffer& buffer) : m_buffer(buffer){}
protected:
    unsigned int m_id;
    VertexBuffer m_buffer;
};