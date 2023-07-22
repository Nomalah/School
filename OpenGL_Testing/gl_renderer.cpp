#include <OpenGL/gl3.h>

#include "gl_renderer.hpp"

void nmlh::gl_renderer::clear(){
    gl_call(glClear(GL_COLOR_BUFFER_BIT));
}

void nmlh::gl_renderer::draw(const vertex_array& va, const index_buffer& ib, const gl_shader& shader) const{
    va.bind();
    ib.bind();
    shader.bind();
    gl_call(glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr));
}