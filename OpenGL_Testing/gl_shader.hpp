#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

struct shader_program_source{
    std::string vertex_source;
    std::string fragment_source;
};

class gl_shader{
    private:
        std::string m_file_path;
        unsigned int m_renderer_id;
        std::unordered_map<std::string, int> m_uniform_locations;
        
        int uniform_location(const std::string& uniform_name);

        unsigned int compile_shader(unsigned int type, const std::string& source);
        shader_program_source parse_shader(const std::string& file_path);
        unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);

    public:
        gl_shader(const std::string& file_path);
        ~gl_shader();

        void bind() const;
        void unbind() const;

        // set uniforms
        void set_uniform_1i(const std::string& uniform_name, int v0);
        void set_uniform_4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);
        void set_uniform_mat4f(const std::string& uniform_name, const glm::mat4 matrix);
};