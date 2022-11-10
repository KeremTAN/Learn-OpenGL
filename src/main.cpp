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
#include <glm/gtx/matrix_transform_2d.hpp> 
// Rotation(Dondurme) Scale(Olcekleme) Translation(Oteleme)
// TxRxS islemleri sirasiyla yapilmalidir.
// TxRxS = Toplam Donusum Matrisi(Dunya Matrisi)
// gtx/...2d s,r,t islemleri icin
#define radian(angle) (angle*3.141592653589793/180)

std::vector<glm::vec3>      vertices;
std::vector<unsigned int>   indicies;

float rotationAngle;
glm::vec2 tranformPosition;
float scale;

unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int elementBufferObject; // indexBufferObject

// 0 1 2
// 0 2 3
// 0 3 4
// ...
// 0 10 11
void createCircle(const float& radius, const float& vertexCount){
    float angle = 360.0f/vertexCount; // f onemli, yoksa yuvarlama yapar;
    int triangleCount = vertexCount -2;
    std::vector<glm::vec3> tempVertices;
    for (int i = 0; i < vertexCount; i++)
    {
        float newAngle=angle*i;
        float x = radius*cos(radian(newAngle));
        float y = radius*sin(radian(newAngle));
        float z = 1.0f;
        vertices.push_back(glm::vec3(x,y,z));
    }

    for (int i = 0; i < triangleCount; i++)
    {
        indicies.push_back(0);
        indicies.push_back(i+1);
        indicies.push_back(i+2);
    }
    
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key==GLFW_KEY_ESCAPE)
        glfwTerminate();
    if (action==GLFW_PRESS)
    {
        if (key==GLFW_KEY_A) {
            tranformPosition.x-=0.05f;
        }
        if (key==GLFW_KEY_D) {
            tranformPosition.x+=0.05f;
        }
        if (key==GLFW_KEY_W) {
            tranformPosition.y+=0.05f;
        }
        if (key==GLFW_KEY_S) {
            tranformPosition.y-=0.05f;
        }
        if (key==GLFW_KEY_Q) {
            scale+=0.05f;
        }
        if (key==GLFW_KEY_E) {
            if(scale!=0.005f)
                scale-=0.05f;
        }
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

    createCircle(0.2,10);
    //********** T R S ********** //
    glm::mat3 mtxTransform(1); //3x3 birim matris
    rotationAngle=0.0f;
    tranformPosition=glm::vec2(0.0f,0.0f);
    scale=1.0f;


    ShaderProgram program;
    program.attachShader("./shaders/simplevs.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/simplefs.glsl",GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uMtxTransform");
    program.addUniform("uColor");

    glGenVertexArrays(1, &vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);

    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*3,(void*)0);

    glEnableVertexAttribArray(0);

    //----
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject); //bind buffer ile EBO aktif ettik.

     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indicies.size(), &indicies[0], GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /*
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1), tranformPosition);
        glm::mat3 mtxRotation = glm::rotate(glm::mat3(1),glm::radians(rotationAngle));
        glm::mat3 mtxScale = glm::scale(glm::mat3(1), glm::vec2(scale,scale));
        mtxTransform=mtxTranslation * mtxRotation * mtxScale;
        */
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1), tranformPosition);
        glm::mat3 mtxRotation = glm::rotate(mtxTranslation,glm::radians(rotationAngle));
        glm::mat3 mtxScale = glm::scale(mtxRotation, glm::vec2(scale,scale));
        mtxTransform= mtxScale;


        rotationAngle+=1.0f;
        program.use();
        glBindVertexArray(vertexArrayObject);

        program.setVec4("uColor", glm::vec4(0.6f,1.0f,1.0f,0.0f));
        program.setMat3("uMtxTransform", &mtxTransform);

        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}