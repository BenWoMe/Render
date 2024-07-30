#pragma once
#include"mesh.hpp"
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
class Model{
public:
    Model(std::string filename): m_filename(filename), m_enableMerge(false){
        LoadModel();
    }

    virtual void Draw(Program& program){
        
        if(m_enableMerge){
            // 启动stencil测试
            GL_ERROR(glEnable(GL_STENCIL_TEST));
            GL_ERROR(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
            GL_ERROR(glStencilMask(0xFF));
            GL_ERROR(glStencilFunc(GL_ALWAYS, 1, 0xFF));
        }
        for(auto& mesh : m_meshes){
            mesh.Draw(program);
        }

        if(m_enableMerge){
            GL_ERROR(glDisable(GL_DEPTH_TEST));
            GL_ERROR(glStencilMask(0x00));
            GL_ERROR(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));

            // 放大
            glm::mat4 model(1.0f);
            model = glm::scale(model, glm::vec3(1.002f, 1.002f, 1.002f));
            m_marginProgram->SetMat4("model", glm::value_ptr(model));

            // 再次绘制
            for(auto& mesh : m_meshes){
                mesh.Draw(*m_marginProgram);
            }

            GL_ERROR(glStencilMask(0xFF));
            GL_ERROR(glEnable(GL_DEPTH_TEST));
            GL_ERROR(glDisable(GL_STENCIL_TEST));
        }

    }
    void EnableMargin(Program& margin) {
        m_enableMerge = true;
        m_marginProgram = &margin;
    }
    void DisableMargin(){
        m_enableMerge = false;
    }
    virtual ~Model(){}
private:
    void LoadModel(){
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_filename, aiProcess_Triangulate | aiProcess_FlipUVs);
        if(!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE){
            throw std::runtime_error("scene doesn't exist.");
            return;
        }
        ProcessNode(scene, scene->mRootNode);
    }
    void ProcessNode(const aiScene* scene, aiNode* node){
        if(scene == nullptr || node == nullptr) return;
        for(int i = 0; i < node->mNumMeshes; ++i) {
            m_meshes.push_back(ProcessMesh(scene, *scene->mMeshes[node->mMeshes[i]])); // 二级mesh指针
        }
        for(int i = 0; i < node->mNumChildren; ++i){
            ProcessNode(scene, node->mChildren[i]);
        }
    }
    void ProcessMaterial();
    Mesh ProcessMesh(const aiScene* scene, const aiMesh& mesh){
        // 获取Vertex
        std::vector<Vertex> vertices;
        for(int i = 0; i < mesh.mNumVertices; ++i){
            Vertex v;
            v.normal.x = mesh.mNormals[i].x;
            v.normal.y = mesh.mNormals[i].y;
            v.normal.z = mesh.mNormals[i].z;

            v.position.x = mesh.mVertices[i].x;
            v.position.y = mesh.mVertices[i].y;
            v.position.z = mesh.mVertices[i].z;

            // 目前只关注0通道的纹理
            v.texCoord.x = mesh.mTextureCoords[0][i].x;
            v.texCoord.y = mesh.mTextureCoords[0][i].y;
            vertices.push_back(v);
        }

        // 获取material
        std::vector<Texture> textures;
        auto materials = scene->mMaterials[mesh.mMaterialIndex];

        std::vector<unsigned int> indices;
        // Faces
        for(int i = 0; i < mesh.mNumFaces; ++i){
            for(int j = 0; j < mesh.mFaces[i].mNumIndices; ++j){
                indices.push_back(mesh.mFaces[i].mIndices[j]);
            }
        }

        return Mesh{vertices, indices, textures};
    }
private:
    std::vector<Mesh> m_meshes;
    std::string m_filename;
    bool m_enableMerge;
    Program* m_marginProgram;
};