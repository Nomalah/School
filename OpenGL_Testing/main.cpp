#include <iostream>

#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Stop OpenGL/gl.h from being included
#define __gl_h_
#include <GLFW/glfw3.h>

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"

#include "gl_texture.hpp"
#include "gl_shader.hpp"
#include "gl_errors.hpp"
#include "gl_renderer.hpp"

using namespace std;

int main(){
    GLFWwindow *window;
    glm::vec4 my_vec;
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int window_height, window_width;
    window = glfwCreateWindow(960, 540, "OpenGL Testing", NULL, NULL);
    if (!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    float positions[]{
        100.0f, 100.0f, 0.0f, 0.0f,
        200.0f, 100.0f, 1.0f, 0.0f,
        200.0f, 200.0f, 1.0f, 1.0f,
        100.0f, 200.0f, 0.0f, 1.0f
    };

    unsigned int indices[]{
        0, 1, 2,
        2, 3, 0
    };

    gl_call(glEnable(GL_BLEND));
    gl_call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    vertex_array va;
    vertex_buffer vb(positions, 4 * 4 * sizeof(float));
    vertex_buffer_layout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    va.add_buffer(vb, layout);

    index_buffer ib(indices, 6);

    glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(400, 200, 0));

    glm::mat4 mvp = proj * view * model;
    // Compile the shader
    gl_shader default_shader("basic.shader");
    default_shader.bind();
    default_shader.set_uniform_mat4f("u_mvp", mvp);
    //default_shader.set_uniform_4f("u_color", 0.0f, 0.0f, 0.0f, 1.0f);

    gl_texture texture("cherno.png");
    texture.bind();
    default_shader.set_uniform_1i("u_texture", 0);

    va.unbind();
    vb.unbind();
    ib.unbind();
    default_shader.unbind();

    nmlh::gl_renderer default_renderer;

    float red = 0.0f;
    float rinc = -0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)){
        /* Render here */
        

        if (red >= 1.0f)
            rinc = -rinc;
        else if (red <= 0.0f)
            rinc = -rinc;

        red += rinc;

        default_shader.bind();
        default_shader.set_uniform_4f("u_color", red, 0.0f, 0.0f, 1.0f);

        default_renderer.clear();
        default_renderer.draw(va, ib, default_shader);
        /* Swap front and back buffers */
        gl_call(glfwSwapBuffers(window));

        /* Poll for and process events */
        gl_call(glfwPollEvents());
    }

    glfwTerminate();
    return 0;
}