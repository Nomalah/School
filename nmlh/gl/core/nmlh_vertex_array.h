#pragma once

#include "../../nmlh_log.hpp"
#include "nmlh_vertex_buffer.h"
#include <OpenGL/gl3.h>

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