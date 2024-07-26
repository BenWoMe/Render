#pragma once
#include"mesh.hpp"
#include<assimp/importer.hpp>
#include<assimp/postprocess.h>
class Model{
public:
    Model(std::string filename): m_filename(filename){
        LoadModel();
    }

private:
    void LoadModel(){
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(m_filename, aiProcess_Triangulate | aiProcess_FlipUVs);

    }
    void ProcessMesh(aiScene* scene, aiNode* node){

    }
    void ProcessMaterial();
private:
    std::string m_filename;
};