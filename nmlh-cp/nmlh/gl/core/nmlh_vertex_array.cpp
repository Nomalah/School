#include "nmlh_vertex_array.h"
#include <iostream>
namespace nmlh::gl::core{
    void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& vbLayout){
        this->bind();
        vb.bind();
        const auto layoutElements = vbLayout.getElements();
        GLuint64 offset = 0;
        for(GLuint i = 0; i < layoutElements.size(); i++){
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, layoutElements[i].count, layoutElements[i].type, 
            layoutElements[i].normalized, vbLayout.getStride(), (const void*)offset);
            offset += layoutElements[i].count * layoutElements[i].sizeOfType();
        } 
    }
}
