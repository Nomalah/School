#include "../../__nmlh_gen_include.h"
#include "nmlh_vertex_buffer.h"

namespace nmlh::core{
    template<typename T>
    void VertexBufferLayout::Push(const unsigned count){
        LOG_ERR("[Invalid Push] push type not explicit", "", 3);
    }

    template<>
    void VertexBufferLayout::Push<float>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_Stride += count * sizeof(GLfloat);
        }
    }

    template<>
    void VertexBufferLayout::Push<unsigned int>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_Stride += count * sizeof(GLuint);
        }
    }

    template<>
    void VertexBufferLayout::Push<unsigned char>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_Stride += count * sizeof(GLubyte);
        }
    }
}