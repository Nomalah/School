#include <OpenGL/gl3.h>

#include "gl_errors.hpp"
#include "gl_texture.hpp"

#include "stb_image.h"

gl_texture::gl_texture(const std::string& path) 
    : m_renderer_id(0), m_file_path(path), m_local_buffer(nullptr), m_width(0), m_height(0), m_bpp(0){
    stbi_set_flip_vertically_on_load(1);
    m_local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
    
    gl_call(glGenTextures(1, &m_renderer_id));
    gl_call(glBindTexture(GL_TEXTURE_2D, m_renderer_id));

    gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    gl_call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    gl_call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_local_buffer));
    gl_call(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_local_buffer)
        stbi_image_free(m_local_buffer);
}

gl_texture::~gl_texture(){
    gl_call(glDeleteTextures(1, &m_renderer_id));
}

void gl_texture::bind(unsigned int slot /* = 0 */) const{
    gl_call(glActiveTexture(GL_TEXTURE0 + slot));
    gl_call(glBindTexture(GL_TEXTURE_2D, m_renderer_id));
}

void gl_texture::unbind() const{
    gl_call(glBindTexture(GL_TEXTURE_2D, 0));
}
