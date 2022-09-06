#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderprogram.hpp"
#include <string>

float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f,  // top   
         0.0f,  0.5f, 0.0f,
         -0.5f, 0.8f, 0.0f,
         0.5f,  0.8f, 0.0f 
}; 

int main(int argc, char** argv){
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(800,800,"First Window", NULL, NULL);

    if (window==NULL)
    {
        std::cout<<"Window creating proccess is unsuccesfuly\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
         std::cout<<"Failed to initilaze GLAD\n";
         return -1;
    }
    ShaderProgram program;
    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();

    unsigned int vertexArrayObject;
    unsigned int vertexBufferObject;


    glGenVertexArrays(1, &vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);


    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);


    // 0. slotu aktif ettik.
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        glBindVertexArray(vertexArrayObject);


        glDrawArrays(GL_TRIANGLES,0,6);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}