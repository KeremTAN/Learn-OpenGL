#include <stdio.h>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

const GLint WIDTH=800, HEIGHT=800;

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

    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input Events
        glfwPollEvents();

        //Clear Window
        glClearColor(1.0f, 0.5f, 0.75f, 0.6f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }
}