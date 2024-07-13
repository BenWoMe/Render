#pragma once
#include<memory>
#include<glm/glm.hpp>
#include<vector>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shader.h"

class Camera{
public:
using vec_type = glm::vec3;
using mat_type = glm::mat4;
    Camera(const vec_type& pos, const vec_type& dir, const vec_type& up,
        const float& fov, const float& aspect, const float& closeFace, const float& farFace, const std::string& view_name = "view")
        : m_pos(pos), m_dir(dir), m_up(up), m_fov(fov), m_aspect(aspect), m_closeFace(closeFace), m_farFace(farFace), 
        m_viewName(view_name){
    }
    void AddProgram(Program& program){
        m_programs.emplace_back(program);
        Update();
    }


    void MoveLeft(float deltaTime) {
        auto leftDir = glm::normalize(glm::cross(m_up, m_dir));
        m_pos += deltaTime * leftDir;
        Update();
    }
    void MoveRight(float deltaTime){
        auto leftDir = glm::normalize(glm::cross(m_up, m_dir));
        m_pos -= deltaTime * leftDir;
        Update();
    }
    void MoveFront(float deltaTime){
        m_pos +=  deltaTime *  glm::normalize(m_dir);
        Update();
    }
    void MoveBack(float deltaTime){
        m_pos -= deltaTime * glm::normalize(m_dir);
        Update();
    }

    void Zoom(float offset){
        m_fov = std::clamp(m_fov += offset, 0.1f, 89.0f);
        Update();
    }

    ~Camera(){
        for(auto& program : m_programs){
            program.Delete();
        }
    }

protected:
    mat_type CalculateProj(){
        return glm::perspective(glm::radians(m_fov), (float)(m_aspect), m_closeFace, m_farFace);
    }
    void Update(){
        for(auto& program : m_programs){
            if(program == 0) return;
            program.SetMat4(m_viewName, glm::value_ptr(GetView()));
            program.SetMat4("projection", glm::value_ptr(CalculateProj()));
        }
    }

    mat_type GetView(){
        return glm::lookAt(m_pos, m_pos + m_dir, m_up);
    }
protected:
// view
    vec_type m_pos;
    vec_type m_dir;
    vec_type m_up;

// projection
    float m_farFace;
    float m_closeFace;
    float m_aspect;
    float m_fov;

    std::string m_viewName;
    std::vector<Program> m_programs;
};