//
// Created by terrapene on 4/9/2023.
//
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "module/shader/Shader.h"
#include "TutorialConfig.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    std::cout << "program start!" << std::endl;
    std::cout<<"version:\t"<< AnimeRenderer_VERSION_MAJOR<<'.'<<AnimeRenderer_VERSION_MINOR<<std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "AnimeRenderer", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
    unsigned int indices[2][3] = {  // note that we start from 0!
            {0, 1, 2},   // first triangle
            {0, 1, 2}    // second triangle
    };
    Shader *shader =new Shader("Shaders/defaultshader.vs.glsl","Shaders/defaultshader.fs.glsl");

#define size 1
    unsigned int VAOs[size], VBOs[size], EBOs[size];
    glGenVertexArrays(size, VAOs);
    glGenBuffers(size, VBOs);
    glGenBuffers(size, EBOs);

    for (int i =0;i<size;i++){

        glBindVertexArray(VAOs[i]);

        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[i]), indices[i], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
    }

    while(!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shader->use();
        for (int i = 0; i < size; i++) {


            glBindVertexArray(VAOs[i]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[i]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteBuffers(2,EBOs);
    delete shader;
    glfwTerminate();
    std::cout << "renderer exit normally" << std::endl;
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}