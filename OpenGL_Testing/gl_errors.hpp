#pragma once

#include <OpenGL/gl3.h>

#define ASSERT(x) if(!(x)) __builtin_debugtrap();
#define gl_call(x) gl_clear_errors();\
    x;\
    ASSERT(gl_log_errors(#x, __FILE__, __LINE__))

void gl_clear_errors();
bool gl_log_errors(const char* function, const char* file, int line);