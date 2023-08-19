#include "nmlh_vertex_array.h"
#include <iostream>
namespace nmlh::core{
    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& vbLayout){
        this->Bind();
        vb.Bind();
        const auto LayoutElements = vbLayout.GetElements();
        GLuint64 offset = 0;
        for(GLuint i = 0; i < LayoutElements.size(); i++){
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, LayoutElements[i].Count, LayoutElements[i].Type, 
            LayoutElements[i].IsNormalized, vbLayout.GetStride(), (const void*)offset);
            offset += LayoutElements[i].Count * LayoutElements[i].SizeOfType();
        } 
    }
}
