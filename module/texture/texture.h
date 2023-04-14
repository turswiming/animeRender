//
// Created by terrapene on 4/14/2023.
//

#ifndef ANIMERENDERER_TEXTURE_H
#define ANIMERENDERER_TEXTURE_H
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Texture {
public:
    Texture(const char* texturePath);
    ~Texture();
    void setToShaderProgram(int typeId);
private:
    unsigned int id;

};


#endif //ANIMERENDERER_TEXTURE_H
