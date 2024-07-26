#pragma once
#include"mesh.hpp"

class Model{
public:
    Model(std::string filename): m_filename(filename){
        LoadModel();
    }

private:
    void LoadModel(){

    }
private:
    std::string m_filename;
};