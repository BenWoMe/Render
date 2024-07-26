#pragma once
#include<glm.hpp>
#include<glad.h>
#include<vector>
#include<string>
#include<stb_image.h>
#include<exception>
#include<format>
#include"shader.h"

#define UNABLED_VERTEX_ARRAY 0

#pragma pack(1)
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
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int> indices ,std::vector<Texture>& textures):
        m_vertices{vertices}, m_indices{indices}, m_textures{textures}{
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), m_vertices.data(), GL_STATIC_DRAW);

            glGenBuffers(1, &VEO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
            glBindVertexArray(UNABLED_VERTEX_ARRAY);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            // 加载纹理
            LoadTextures();
        }

    void Draw(Program& program){
        glBindVertexArray(VAO);
        program.Use();
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, m_indices.data());
    }
protected:
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