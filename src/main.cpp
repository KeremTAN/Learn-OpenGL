#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include "shaderprogram.hpp"
#include "square.hpp"
#include <string>
#include <thread>
#include <chrono>

float length =0.08f;
Square square1(0.0f,0.0f,length);
glm::vec3 positon = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec4 color1 = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
glm::vec4 color2 = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
glm::vec4 color3 = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
float vertices[] = {
        -length/2,  length/2, 0,
        -length/2, -length/2, 0,
         length/2, -length/2, 0,

        -length/2,  length/2, 0,
         length/2, -length/2, 0,
         length/2,  length/2, 0
};
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
float moveInc = 0.0f;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_A)
            square1.setDirection(Square::DIR_LEFT);
        if (key==GLFW_KEY_D)
            square1.setDirection(Square::DIR_RIGHT);
        if (key==GLFW_KEY_W)
            square1.setDirection(Square::DIR_UP);
        if (key==GLFW_KEY_S)
            square1.setDirection(Square::DIR_DOWN);
    }
    
}
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
    glfwSetKeyCallback(window,key_callback);
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
    program.addUniform("uMove");
    program.addUniform("uColor");

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

        program.setVec3("uMove",square1.getPosition());
        program.setVec4("uColor",square1.getColor());
        glDrawArrays(GL_TRIANGLES,0,6);

        square1.move();
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}