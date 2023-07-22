#pragma once

#include <vector>
#include <OpenGL/gl3.h>

#include "gl_errors.hpp"

struct vertex_buffer_element{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    unsigned int size_of_type() const{
        switch(type){
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class vertex_buffer_layout{
    private:
        std::vector<vertex_buffer_element> m_elements;
        unsigned int m_stride;
    public:
        vertex_buffer_layout();

        template<typename T>
        void push(unsigned int count);

        const std::vector<vertex_buffer_element>& get_elements() const;

        unsigned int get_stride() const;
};