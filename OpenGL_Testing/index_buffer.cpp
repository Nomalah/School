#include <OpenGL/gl3.h>

#include "index_buffer.hpp"
#include "gl_errors.hpp"

index_buffer::index_buffer(const unsigned int* data, unsigned int count) : m_count(count){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    gl_call(glGenBuffers(1, &m_buffer_id));
    gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id));
    gl_call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}   

index_buffer::~index_buffer(){
    gl_call(glDeleteBuffers(1, &m_buffer_id));
}   

void index_buffer::bind() const{
    gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffer_id));
}   

void index_buffer::unbind() const{
    gl_call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}   