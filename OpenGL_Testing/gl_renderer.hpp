#pragma once

#include "gl_shader.hpp"

#include "vertex_array.hpp"
#include "index_buffer.hpp"

namespace nmlh{
    class gl_renderer{
        private:

        public:
            void clear();
            void draw(const vertex_array& va, const index_buffer& ib, const gl_shader& shader) const;
};
}