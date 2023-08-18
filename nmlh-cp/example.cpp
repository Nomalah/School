// EXAMPLE PROGRAM
// Draws a Square to the screen

// Irrelivent to actual program
#include <iostream>

// In the final version, you should only have to include this file
#include "nmlh/nmlh.h"

int main(){
    //******************************************************
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
    //******************************************************

    // Set Framerate to Vsync
    glfwSwapInterval(1);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[]{
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };
    
    nmlh::gl::core::vertexArray vao;
    vao.bind();

    nmlh::gl::core::vertexBufferLayout vbLayout;
    vbLayout.push<float>(2);

    nmlh::gl::core::vertexBuffer vb;
    vb.loadBuffer(positions, 6 * vbLayout.getStride());

    vao.addBuffer(vb, vbLayout);
    
    // Compile the shader
    nmlh::gl::util::shader default_shader("shader.glsl");
    default_shader.bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // THis should be abstracted
        glDrawArrays(GL_TRIANGLES, 0, 6);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    

    glfwTerminate();
    return 0;
}