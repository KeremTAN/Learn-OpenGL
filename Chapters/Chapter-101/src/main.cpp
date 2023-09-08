#include <stdio.h>
#include <string>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH=800, HEIGHT=800;

GLuint VAO, VBO, shaderProgram;

// Vertex Shader
static const char* vShader = "                              \n\
#version 330                                                \n\
layout (location=0) in vec3 pos;                            \n\
void main() {                                               \n\
    gl_Position = vec4(0.4*pos.x, 0.4*pos.y, pos.z, 1.0);   \n\
}";

// Fragment Shader
static const char* fShader = "                      \n\
#version 330                                        \n\
out vec4 colour;                                    \n\
void main() {                                       \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);              \n\
}";

void createTriangle(){
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinding VBO
    glBindVertexArray(0); // unbinding VAO
}


void AddShader(GLuint theShaderProgram, const char* shaderCode, GLenum shaderType){

    GLuint shader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, theCode, codeLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("The Error compiling shader : '%s'\n", eLog);
        return;
    }

    glAttachShader(theShaderProgram, shader);

    return;
}

void CompileShaders(){
    shaderProgram = glCreateProgram();

    if(!shaderProgram) {
        printf("Error creating shader program!\n");
        return;
    }

    AddShader(shaderProgram, vShader, GL_VERTEX_SHADER);
    AddShader(shaderProgram, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
        printf("The program linking error : '%s'\n", eLog);
        return;
    }

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderProgram, sizeof(eLog), NULL, eLog);
        printf("The program validateing error : '%s'\n", eLog);
        return;
    }
}

int main(int argc, char** argv){


    if (!glfwInit()){
         printf("GLFW initialisation proccess is unsuccesfuly\n");
        return -1;
    }

    // Setup GLFW properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Core Profile = Not Backwards Compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    // Allow Forward Compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH,HEIGHT,"First Window", NULL, NULL);

    if (!mainWindow)
    {
        printf("Window creating proccess is unsuccesfuly\n");
        glfwTerminate();
        return -1;
    }

    //GET BUFFER SIZE INFORMATION
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // SET CONTEXT FOR GLEW TO USE
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extension features 
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK){
        printf("GLEW initialisation is unsuccesfuly\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //Setup ViewPort Size
    glViewport(0,0,bufferWidth, bufferHeight);

    createTriangle();
    CompileShaders();

    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input Events
        glfwPollEvents();

        //Clear Window
        glClearColor(0.0f, 0.0f, 0.0f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }
}