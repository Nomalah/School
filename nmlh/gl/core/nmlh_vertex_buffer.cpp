#include <OpenGL/gl3.h>

#include "../../nmlh_log.hpp"
#include "nmlh_vertex_buffer.h"

namespace nmlh::gl::core{
    template<typename T>
    void vertexBufferLayout::push(const unsigned count){
        LOG_ERR("[Invalid Push] push type not explicit", "", 3);
    }

    template<>
    void vertexBufferLayout::push<float>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
            m_Stride += count * sizeof(GLfloat);
        }
    }

    template<>
    void vertexBufferLayout::push<unsigned int>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
            m_Stride += count * sizeof(GLuint);
        }
    }

    template<>
    void vertexBufferLayout::push<unsigned char>(const unsigned count){
        if(4 < count || count < 1){
            LOG_ERR("[Invalid Push] push count ", count, 3);
        }else{
            m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
            m_Stride += count * sizeof(GLuint);
        }
    }
}