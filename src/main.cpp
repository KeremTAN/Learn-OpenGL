#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/vec3.hpp>
#include<glm/vec4.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include "shaderprogram.hpp"
#include "square.hpp"

float length =0.08f;
float vertices[] = {
        -length/2,  length/2, 0,
        -length/2, -length/2, 0,
         length/2, -length/2, 0,

        -length/2,  length/2, 0,
         length/2, -length/2, 0,
         length/2,  length/2, 0
};
std::vector<Square*>    snakeList;


unsigned int vertexArrayObject;
unsigned int vertexBufferObject;

void moveSnake(){
    
    for (auto s : snakeList)
        s->move();
    
    for (int i = snakeList.size()-1; i>0; i--)
    {
        snakeList[i]->setDirection(snakeList[i-1]->getDirection());
      
    }
    
}

void drawSnake(ShaderProgram& program){
    for (auto next : snakeList)
        {
            program.setVec3("uMove",next->getPosition());
            program.setVec4("uColor",next->getColor());
            glDrawArrays(GL_TRIANGLES,0,6);
        }
}

void addToSnakeTail(){
    int snakeSize = snakeList.size();
    if (snakeSize==0){
        snakeList.push_back(new Square(0.0f,0.0f, length));
    }
    else{
        Square* lastSquare = snakeList[snakeSize-1]; 
        glm::vec3 posOfLS = lastSquare->getPosition();
        Square::DIRECTION dirOfLS = lastSquare->getDirection();
        switch (dirOfLS)
        {
            case Square::DIR_RIGHT:
                posOfLS-=glm::vec3(length,0.0f,0.0f);
                break;
            case Square::DIR_LEFT:
                posOfLS+=glm::vec3(length,0.0f,0.0f);
                break;
            case Square::DIR_UP:
                posOfLS-=glm::vec3(0.0f,length,0.0f);
                break;
            case Square::DIR_DOWN:
                posOfLS+=glm::vec3(0.0f,length,0.0f);
                break;
            default:
                break;
        }
        Square* newSquare = new Square(posOfLS.x, posOfLS.y, length);
        newSquare->setDirection(dirOfLS);
        snakeList.push_back(newSquare);
    }  
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (snakeList.size()!=0)
        {
            Square* first = snakeList[0];
            if (key==GLFW_KEY_A);
                first->setDirection(Square::DIR_LEFT);
            if (key==GLFW_KEY_D)
                first->setDirection(Square::DIR_RIGHT);
            if (key==GLFW_KEY_W)
                first->setDirection(Square::DIR_UP);
            if (key==GLFW_KEY_S)
                first->setDirection(Square::DIR_DOWN);
            if (key==GLFW_KEY_SPACE)
                addToSnakeTail();
        }
        
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

    addToSnakeTail();
    addToSnakeTail();
    addToSnakeTail();
    addToSnakeTail();
    addToSnakeTail();

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

        drawSnake(program);
        moveSnake();

        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}