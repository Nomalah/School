#pragma once

#include "../../__nmlh_gen_include.h"
#include <vector>

namespace nmlh::core{
    class VertexBuffer{
        private:
            GLuint m_RendererId;
        public:
            VertexBuffer() : m_RendererId(0){};
            ~VertexBuffer(){glDeleteBuffers(1, &m_RendererId);};

            void LoadBuffer(const void* RawVertexData, size_t DataSize){
                glDeleteBuffers(1, &m_RendererId);
                glGenBuffers(1, &m_RendererId);
                glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
                glBufferData(GL_ARRAY_BUFFER, DataSize, RawVertexData, GL_STATIC_DRAW);
            }   

            void Bind() const{glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);};
            void UnBind() const{glBindBuffer(GL_ARRAY_BUFFER, 0);};
    };

    struct VertexBufferElement{
        GLenum Type;
        unsigned Count;
        GLboolean IsNormalized;
        
        unsigned SizeOfType() const{
            switch(Type){
                case GL_FLOAT: return sizeof(GLfloat);
                case GL_UNSIGNED_INT: return sizeof(GLuint);
                case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
            }
            LOG_ERR("[Invalid Buffer Layout Type] ", Type, 1);
            return 0;
        }
    };

    class VertexBufferLayout{
        private: 
            std::vector<VertexBufferElement> m_Elements;
            unsigned m_Stride;
        
        public:
            VertexBufferLayout() : m_Stride(0){}

            template<typename T>
            void Push(const unsigned count);

            const std::vector<VertexBufferElement>& GetElements() const{return m_Elements;};
            unsigned GetStride() const{return m_Stride;};
    };
};