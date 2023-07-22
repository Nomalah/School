#include "gl_errors.hpp"

#include "vertex_buffer.hpp"
#include "vertex_array.hpp"

vertex_array::vertex_array(){
    gl_call(glGenVertexArrays(1, &m_renderer_id));
}

vertex_array::~vertex_array(){
    gl_call(glDeleteVertexArrays(1, &m_renderer_id));
}

void vertex_array::add_buffer(const vertex_buffer& vb, const vertex_buffer_layout& layout){
    this->bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for(size_t i = 0; i < elements.size(); i++){
        gl_call(glEnableVertexAttribArray(i));
        gl_call(glVertexAttribPointer(i, elements[i].count, elements[i].type, elements[i].normalized, layout.get_stride(), (const void*)offset));
        offset += elements[i].count * elements[i].size_of_type();
    }
}

void vertex_array::bind() const{
    gl_call(glBindVertexArray(m_renderer_id));
}

void vertex_array::unbind() const{
    gl_call(glBindVertexArray(0));
}