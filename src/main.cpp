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
#include "square.hpp"
#include "texturemanager.hpp"

// Rotation(Dondurme) Scale(Olcekleme) Translation(Oteleme)
// TxRxS islemleri sirasiyla yapilmalidir.
// TxRxS = Toplam Donusum Matrisi(Dunya Matrisi)
// gtx/...2d s,r,t islemleri icin
#define radian(angle) (angle*3.141592653589793/180)

struct Vertex{
    glm::vec3 pos;
    glm::vec2 tex;
};
std::vector<Vertex>         vertices;
std::vector<unsigned int>   indicies;

float rotationAngle;
glm::vec2 tranformPosition;
float scale;

unsigned int vertexArrayObject;
unsigned int vertexBufferObject;
unsigned int elementBufferObject; // indexBufferObject
unsigned int texture;

void createSquare(const float& length){
    Vertex v0, v1, v2, v3;
    v0.pos=glm::vec3(-length/2, length/2, 0.0f);
    v1.pos=glm::vec3(-length/2,-length/2, 0.0f);
    v2.pos=glm::vec3( length/2,-length/2, 0.0f);
    v3.pos=glm::vec3( length/2, length/2, 0.0f);

    v0.tex=glm::vec2(0.0f, 1.0f);
    v1.tex=glm::vec2(0.0f, 0.0f);
    v2.tex=glm::vec2(1.0f, 0.0f);
    v3.tex=glm::vec2(1.0f, 1.0f);

    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);

    indicies.push_back(0);
    indicies.push_back(1);
    indicies.push_back(3);

    indicies.push_back(1);
    indicies.push_back(2);
    indicies.push_back(3);
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

// SQUARE TEXTURE
    createSquare(1);

    int width, height, nrChannels; 
    texture = TextureManager::getInstance()->loadTexture("./images/container.jpg");

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

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    //POSITION
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)0);

    glEnableVertexAttribArray(0);

    //TEXTURE
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,sizeof(float)*5,(void*)(3*sizeof(float)));

    glEnableVertexAttribArray(1);

    //----
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject); //bind buffer ile EBO aktif ettik.

     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*indicies.size(), &indicies[0], GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /*
           mtxTranslation * mtxRotation * mtxScale;
        */
        glm::mat3 mtxTranslation = glm::translate(glm::mat3(1), tranformPosition);
        glm::mat3 mtxRotation = glm::rotate(mtxTranslation,glm::radians(rotationAngle));
        glm::mat3 mtxScale = glm::scale(mtxRotation, glm::vec2(scale,scale));
        mtxTransform= mtxScale;


        rotationAngle+=1.0f;
        program.use();
        TextureManager::getInstance()->activeTexture(GL_TEXTURE0, texture);

        glBindVertexArray(vertexArrayObject);

        program.setVec4("uColor", glm::vec4(0.6f,1.0f,1.0f,0.0f));
        program.setMat3("uMtxTransform", &mtxTransform);

        glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(60));

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}