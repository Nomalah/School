#pragma once

#include <OpenGL/gl3.h>
#include <vector>
#include "../../nmlh_log.hpp"

namespace nmlh::gl::core{
    class vertexBuffer{
        private:
            GLuint m_RendererId;
        public:
            vertexBuffer() : m_RendererId(0){};
            ~vertexBuffer(){glDeleteBuffers(1, &m_RendererId);};

            void loadBuffer(const void* data, unsigned size){
                glDeleteBuffers(1, &m_RendererId);
                glGenBuffers(1, &m_RendererId);
                glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
                glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
            }   

            void bind() const{glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);};
            void unbind() const{glBindBuffer(GL_ARRAY_BUFFER, 0);};
    };

    struct vertexBufferElement{
        GLenum type;
        unsigned count;
        GLboolean normalized;
        
        unsigned sizeOfType() const{
            switch(type){
                case GL_FLOAT: return sizeof(GLfloat);
                case GL_UNSIGNED_INT: return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
            }
            LOG_ERR("[Invalid Buffer Layout Type] ", type, 1);
            return 0;
        }
    };

    class vertexBufferLayout{
        private: 
            std::vector<vertexBufferElement> m_Elements;
            unsigned m_Stride;
        
        public:
            vertexBufferLayout() : m_Stride(0){}

            template<typename T>
            void push(const unsigned count);

            const std::vector<vertexBufferElement>& getElements() const{return m_Elements;};
            unsigned getStride() const{return m_Stride;};
    };
};