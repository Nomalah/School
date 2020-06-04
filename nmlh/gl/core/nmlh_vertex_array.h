#pragma once

#include "../../__nmlh_gen_include.h"
#include "nmlh_vertex_buffer.h"

namespace nmlh::core{
    class VertexArray{
        private:
            GLuint m_RendererId;
        public:
            VertexArray(){glGenVertexArrays(1, &m_RendererId);}
            ~VertexArray(){glDeleteVertexArrays(1, &m_RendererId);}
            
            void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout);

            void Bind() const{glBindVertexArray(m_RendererId);}
            void UnBind() const{glBindVertexArray(0);}
    };
}