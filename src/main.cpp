#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "shaderprogram.hpp"

#define radian(angle) (angle*3.141592653589793/180)
std::vector<glm::vec3> vertices;
unsigned int vertexArrayObject;
unsigned int vertexBufferObject;

void createCircle(const float& radius, const float& vertexCount){
    float angle = 360.0f/vertexCount;
    int triangleCount = vertexCount -2;
    std::vector<glm::vec3> tempVertices;
    for (int i = 0; i < vertexCount; i++)
    {
        float newAngle=angle*i;
        float x = radius*cos(radian(newAngle));
        float y = radius*sin(radian(newAngle));
        float z = 0.0f;
        tempVertices.push_back(glm::vec3(x,y,z));
    }
    for (int i = 0; i < triangleCount; i++)
    {
        vertices.push_back(tempVertices[0]);
        vertices.push_back(tempVertices[i+1]);
        vertices.push_back(tempVertices[i+2]);
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_A); {}
        if (key==GLFW_KEY_D) {}
        if (key==GLFW_KEY_W) {}
        if (key==GLFW_KEY_S) {}
        if (key==GLFW_KEY_SPACE) {}   
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

    createCircle(1,12);

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

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);

    // 0. slotu aktif ettik.
    glEnableVertexAttribArray(0);
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glBindVertexArray(vertexArrayObject);

        program.setVec3("uMove",glm::vec3(0.0f,0.0f,0.0f));
        program.setVec4("uColor", glm::vec4(1.0f,0.0f,0.0f,0.0f));

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}