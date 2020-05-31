// EXAMPLE PROGRAM
// Draws a Square to the screen

// Irrelivent to actuall program
#include <iostream>

// In the final version, you should only have to include this file
#include "nmlh/nmlh.h"

int main(){
    // You should not have to do this in the final version
    GLFWwindow* window = nullptr;

    // GLFW did not initialize correctly
    if(!glfwInit()){
        return -1;
    }
    
    /* Create a windowed mode window and its OpenGL context */
    // Set the OpenGL version to 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Make OpenGL forward compatable
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Use the OpenGL core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a 960px * 540px window
    window = glfwCreateWindow(960, 540, "NMLH example", NULL, NULL);

    // If the window was not created successfully
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Set Framerate to Vsync
    glfwSwapInterval(1);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glfwTerminate();
    return 0;
}