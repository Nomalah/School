#include <OpenGL/gl3.h>

#include "vertex_buffer.hpp"
#include "gl_errors.hpp"

vertex_buffer::vertex_buffer(const void* data, unsigned int size){
    gl_call(glGenBuffers(1, &m_buffer_id));
    gl_call(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
    gl_call(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}   

vertex_buffer::~vertex_buffer(){
    gl_call(glDeleteBuffers(1, &m_buffer_id));
}   

void vertex_buffer::bind() const{
    gl_call(glBindBuffer(GL_ARRAY_BUFFER, m_buffer_id));
}   

void vertex_buffer::unbind() const{
    gl_call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}   