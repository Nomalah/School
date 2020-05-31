/* 
 * This File will include all other files, 
 * and if you are importing to your own project,
 * this is most likely the way to go.
 * 
 * Copyright May 29 2020 Dallas Hart
 */

#pragma once

#if defined(__APPLE__)
    #include <OpenGL/gl3.h>
#else
    #include <GL/gl3.h>
#endif

// Stop gl.h from being included
#define __gl_h_
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "gl/core/nmlh_vertex_buffer.h"
#include "gl/util/nmlh_shader.h"
#include "nmlh_log.hpp"