#pragma once
#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>
#include<string>
#include<stb_image.h>
#include<exception>
#include<format>
#include"shader.h"
#include"gl_utility.hpp"

#define UNABLED_VERTEX_ARRAY 0

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

struct Texture{
    unsigned int id;
    std::string type;
    std::string filename;
};


class Mesh{
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices ,std::vector<Texture> textures):
        m_vertices{vertices}, m_indices{indices}, m_textures{textures}{
        Init();
    }

    Mesh(const Mesh& other){
        m_vertices = other.m_vertices;
        m_indices = other.m_indices;
        m_textures = other.m_textures;
        VAO = other.VAO;
        VBO = other.VBO;
        VEO = other.VEO;
    }

    Mesh& operator=(const Mesh& other){
        if(&other == this) return *this;
        m_vertices = other.m_vertices;
        m_indices = other.m_indices;
        m_textures = other.m_textures;
        VAO = other.VAO;
        VBO = other.VBO;
        VEO = other.VEO;
        return *this;
    }

    void Draw(Program& program){
        GL_ERROR(glBindVertexArray(VAO));
        program.Use();
        GL_ERROR(glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, m_indices.data()));
        GL_ERROR(glBindVertexArray(0));
        program.UnUse();
    }
protected:
    void Init(){
        GL_ERROR(glGenVertexArrays(1, &VAO));
        GL_ERROR(glBindVertexArray(VAO));

        GL_ERROR(glGenBuffers(1, &VBO));
        GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        GL_ERROR(glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW));

        GL_ERROR(glGenBuffers(1, &VEO));
        GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO));
        GL_ERROR(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW));

        GL_ERROR(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)));
        GL_ERROR(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)));
        GL_ERROR(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord)));
        GL_ERROR(glEnableVertexAttribArray(0));
        GL_ERROR(glEnableVertexAttribArray(1));
        GL_ERROR(glEnableVertexAttribArray(2));
        // 加载纹理
        //LoadTextures();

        // 解绑VAO
        GL_ERROR(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_ERROR(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GL_ERROR(glBindVertexArray(UNABLED_VERTEX_ARRAY));
    }

    void LoadTextures(){ // 再考虑一下纹理的加载过程
        int diffCnt = 0;
        int speCnt = 0; 
        for(int i = 0; i < m_textures.size(); ++i){
            glGenTextures(1, &m_textures[i].id);
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            {
                int width, height, channel;
                unsigned char* data = stbi_load(m_textures[i].filename.c_str(), &width, &height, &channel, 0);
                if(!data){
                    throw std::runtime_error(std::format("texture : {} doesn't exist.", m_textures[i].filename));
                    return ;
                }

                auto format = (channel == 3 ? GL_RGB : GL_RGBA);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
                stbi_image_free(data);
            }
        } 
    }
protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_textures;
    unsigned int VAO, VBO, VEO;
};