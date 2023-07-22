#pragma once

#include "gl_renderer.hpp"

class gl_texture{
    private:
        unsigned int m_renderer_id;
        std::string m_file_path;
        unsigned char* m_local_buffer;
        int m_width, m_height, m_bpp;
    public:
        gl_texture(const std::string& file_path);
        ~gl_texture();

        void bind(unsigned int slot = 0) const;
        void unbind() const;

        inline int width() const{
            return m_width;
        }  
        inline int height() const{
            return m_height;
        }
};