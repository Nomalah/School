#pragma once

#include "../../__nmlh_gen_include.h"
#include "nmlh_vertex_buffer.h"

namespace nmlh::gl::core{
    class vertexArray{
        private:
            GLuint m_RendererId;
        public:
            vertexArray(){glGenVertexArrays(1, &m_RendererId);};
            ~vertexArray(){glDeleteVertexArrays(1, &m_RendererId);};
            
            void addBuffer(const vertexBuffer& vb, const vertexBufferLayout& vbLayout);

            void bind() const{glBindVertexArray(m_RendererId);};
            void unbind() const{glBindVertexArray(0);};
    };
}