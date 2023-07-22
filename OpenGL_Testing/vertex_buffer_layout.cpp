#include "vertex_buffer_layout.hpp"

#include "gl_errors.hpp"

vertex_buffer_layout::vertex_buffer_layout() : m_stride(0){

};

template<typename T>
void vertex_buffer_layout::push(unsigned int count){
    ASSERT(false);
}

template<>
void vertex_buffer_layout::push<float>(unsigned int count){
    m_elements.push_back({GL_FLOAT, count, GL_FALSE});
    m_stride += count * sizeof(GLfloat);
}  

template<>
void vertex_buffer_layout::push<unsigned int>(unsigned int count){
    m_elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += count * sizeof(GLint);
}

template<>
void vertex_buffer_layout::push<unsigned char>(unsigned int count){
    m_elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
    m_stride += count * sizeof(GLbyte);
}

const std::vector<vertex_buffer_element>& vertex_buffer_layout::get_elements() const{
    return m_elements;
}

unsigned int vertex_buffer_layout::get_stride() const {
    return m_stride;
}