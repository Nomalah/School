#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <OpenGL/gl3.h>

#include "gl_shader.hpp"
#include "gl_errors.hpp"

shader_program_source gl_shader::parse_shader(const std::string& file_path){
    std::ifstream file_stream(file_path);

    enum class shader_type{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream shader_streams[2];
    shader_type type = shader_type::NONE;
    while(std::getline(file_stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos)
                type = shader_type::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = shader_type::FRAGMENT;
        }else{
            shader_streams[(int)type] << line << '\n';
        }
    }

    return {shader_streams[0].str(), shader_streams[1].str()};
}


unsigned int gl_shader::compile_shader(unsigned int type, const std::string& source){
    gl_call(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();

    // Pass in the id, the number of source files, a pointer to the raw sources,
    // and the length of the source (nullptr if the whole source)
    gl_call(glShaderSource(id, 1, &src, nullptr));
    gl_call(glCompileShader(id));

    // Check if the compile was successful
    int successful;
    gl_call(glGetShaderiv(id, GL_COMPILE_STATUS, &successful));
    if(successful == GL_FALSE){
        // Get the length of the error message
        int length;
        gl_call(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        // Allocate for the error message
        char* err_message = (char*)alloca(length * sizeof(char));

        // Retrive the error message
        gl_call(glGetShaderInfoLog(id, length, &length, err_message));

        // Output the error message
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << std::endl;
        std::cerr << err_message << std::endl;

        // Delete the failed shader
        gl_call(glDeleteShader(id));
        return 0;
    }
    return id;
}

unsigned int gl_shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader){
    // Create the shader program
    gl_call(unsigned int program = glCreateProgram());

    // Create the vertex and Fragment shaders
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    // Attach the shaders to the program
    gl_call(glAttachShader(program, vs));
    gl_call(glAttachShader(program, fs));

    // Link all the shaders together
    gl_call(glLinkProgram(program));

    // Validate that the program linked and compiled correctly
    gl_call(glValidateProgram(program));
    
    int successful;
    gl_call(glGetProgramiv(program, GL_VALIDATE_STATUS, &successful));
    if(successful == GL_FALSE) {
        // Get the length of the error message
        int length;
        gl_call(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));

        // Allocate for the error message
        char* err_message = (char*)alloca(length * sizeof(char));

        // Retrive the error message
        gl_call(glGetProgramInfoLog(program, length, &length, err_message));

        // Output the error message
        std::cerr << "Failed to validate shader: " << std::endl;
        std::cerr << err_message << std::endl;

        return 0;
    }

    // After linking, you can delete the shaders
    gl_call(glDeleteShader(vs));
    gl_call(glDeleteShader(fs));

    return program;
}

gl_shader::gl_shader(const std::string& file_path) : m_file_path(file_path), m_renderer_id(0){
    shader_program_source source = parse_shader(file_path);
    m_renderer_id = create_shader(source.vertex_source, source.fragment_source);
}

gl_shader::~gl_shader(){
    gl_call(glUseProgram(0))
    gl_call(glDeleteProgram(m_renderer_id));
}

void gl_shader::bind() const{
    gl_call(glUseProgram(m_renderer_id));
}

void gl_shader::unbind() const{
    gl_call(glUseProgram(0));
}

int gl_shader::uniform_location(const std::string& uniform_name){
    if(m_uniform_locations.find(uniform_name) != m_uniform_locations.end())
        return m_uniform_locations[uniform_name];
    
    gl_call(unsigned int location = glGetUniformLocation(m_renderer_id, uniform_name.c_str()));
    if(location == -1)
        std::cerr << "\033[38;5;11m[Warning]\n\t" << "[Uniform Invalid] " << uniform_name << "\033[38;5;7m\n";
    m_uniform_locations[uniform_name] = location;
    return location;
}

void gl_shader::set_uniform_1i(const std::string& uniform_name, int v0){
    gl_call(glUniform1i(uniform_location(uniform_name), v0));
}

void gl_shader::set_uniform_4f(const std::string& uniform_name, float v0, float v1, float v2, float v3){
    gl_call(glUniform4f(uniform_location(uniform_name), v0, v1, v2, v3));
}
void gl_shader::set_uniform_mat4f(const std::string& uniform_name, const glm::mat4 matrix){
    gl_call(glUniformMatrix4fv(uniform_location(uniform_name), 1, GL_FALSE, &matrix[0][0]));
}