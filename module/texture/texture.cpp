//
// Created by terrapene on 4/14/2023.
//
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char * texturePath){
    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath,&width,&height,&nrChannels,0);
    unsigned int texture ;

    if(data){
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        if(nrChannels==4){
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        } else{
            glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    }else{
        std::cout<<"Failed to load texture: "<< texturePath<<std::endl;
    }
    stbi_image_free(data);
    this->id=texture;
}
Texture::~Texture() {
    glDeleteTextures(1,&(this->id));
}
void Texture::setToShaderProgram(int typeId){
//    glActiveTexture(typeId);
    glBindTexture(GL_TEXTURE_2D,this->id);

}
