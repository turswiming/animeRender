//
// Created by terrapene on 4/9/2023.
//

#ifndef ANIMERENDERER_SHADER_H
#define ANIMERENDERER_SHADER_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Shader{
public:
    unsigned int ID;
    Shader(const char*vertexPath,const char * fragmentPath);
    ~Shader();
    void use();
    void setBool(const std::string &name,bool value)const;
    void setInt(const std::string &name,int value)const;
    void setFloat(const std::string &name,float value)const;
    void setTexture(const std::string &name,float value)const;
    void setMatrix(const std::string &name,glm::mat4 trans )const;

};
#endif //ANIMERENDERER_SHADER_H
