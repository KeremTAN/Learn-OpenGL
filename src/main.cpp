#include <iostream>
#include <GLFW/glfw3.h>
#include "lib.hpp"

int main(int argc, char** argv){


    if (!glfwInit())
        return -1;

    GLFWwindow* window = glfwCreateWindow(800,800,"First Window", NULL, NULL);

    if (window==NULL)
    {
        std::cout<<"Window creating proccess is unsuccesfuly\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}