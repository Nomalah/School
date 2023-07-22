#include <iostream>
#include <OpenGL/gl3.h>

#include "gl_errors.hpp"

void gl_clear_errors(){
    while(glGetError() != GL_NO_ERROR);
}

bool gl_log_errors(const char* function, const char* file, int line){
    bool flag = true;
    while(GLenum current_error = glGetError()){
        std::cerr << "\033[38;5;9m[OpenGL Error]\n\t";
        std::cerr << "[Error Code] 0x" << std::hex << current_error << ", " << std::dec << current_error << "\n\t";
        std::cerr << "[Function] " << function << "\n\t";
        std::cerr << "[File] " << file << "\n\t";
        std::cerr << "[Line] " << line << "\n\033[38;5;7m";
        flag = false;
    }
    return flag;
}