#include <fstream>
#include <sstream>
#include <string>

#include "../../__nmlh_gen_include.h"
#include "nmlh_shader.h"

namespace nmlh::gl::util{
    const unsigned shaderTypes = 2;

    shader::shader(const std::string& shaderSource) : m_RendererId(glCreateProgram()){        
        std::ifstream shaderFile(shaderSource);

        if(!shaderFile.is_open()){
            LOG_ERR("[Couldn't Open File] ", shaderSource, 3);
            m_RendererId = 0;
            return;
        }

        std::stringstream shaders[shaderTypes];

        enum shaderType{
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
            GEOMETRY = 2
        };
        
        shaderType curShader = shaderType::NONE;

        std::string line = "";
        while(getline(shaderFile, line)){
            if(line.find("#shader ") != std::string::npos){
                if(line.find("vertex", 8) != std::string::npos)
                    curShader = shaderType::VERTEX;
                else if(line.find("fragment", 8) != std::string::npos)
                    curShader = shaderType::FRAGMENT;
                else if(line.find("geometry", 8) != std::string::npos)
                    curShader = shaderType::GEOMETRY;
            }else{
                if(curShader != shaderType::NONE){
                    shaders[curShader] << line << '\n';
                }
            }
        }

        GLuint shaderId[shaderTypes];
        for(unsigned i = 0; i < shaderTypes; i++){
            std::string shader = shaders[i].str();
            switch(i){
                case shaderType::VERTEX:
                    shaderId[i] = compileShader(GL_VERTEX_SHADER, shader);
                    break;
                case shaderType::FRAGMENT:
                    shaderId[i] = compileShader(GL_FRAGMENT_SHADER, shader);
                    break;
                case shaderType::GEOMETRY:
                    shaderId[i] = compileShader(GL_GEOMETRY_SHADER, shader);
            }
            glAttachShader(m_RendererId, shaderId[i]);
        }
        glLinkProgram(m_RendererId);

        // Check if the program is a valid shader
        GLint success;
        glValidateProgram(m_RendererId);
        glGetProgramiv(m_RendererId, GL_VALIDATE_STATUS, &success);
        if(success == GL_FALSE){
            int messageLength;
            glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &messageLength);
            char* errMessage = new char[messageLength];
            if(errMessage == nullptr){
                LOG_ERR("[Alloc Fail] ", "char* message = new char[messageLength];", 3);
            }else{
                glGetProgramInfoLog(m_RendererId, messageLength, &messageLength, errMessage);
                LOG_ERR("[Shader Vallidation Failed] ", errMessage, 2);
            }

            m_RendererId = 0;
        }
        
        for(unsigned i = 0; i < shaderTypes; i++){
            glDeleteShader(shaderId[i]);
        }
    }

    GLuint shader::compileShader(GLenum type, const std::string& source){
        GLuint shaderId = glCreateShader(type);
        const char* shaderSrc = source.c_str();

        glShaderSource(shaderId, 1, &shaderSrc, nullptr);
        glCompileShader(shaderId);

        // Check if the compile was successful
        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if(success == GL_FALSE){
            int messageLength;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &messageLength);
            char* errMessage = new char[messageLength];
            if(errMessage == nullptr){
                LOG_ERR("[Alloc Fail] ", "char* message = new char[messageLength];", 3);
            }else{
                glGetShaderInfoLog(shaderId, messageLength, &messageLength, errMessage);
                LOG_ERR("[Shader Compilation Failed] ", errMessage, 2);
            }

            return 0;
        }
        
        return shaderId;
    }

    GLint shader::getUniformLocation(const std::string& uniformName){
        if(m_UniformLocation.find(uniformName) != m_UniformLocation.end())
            return m_UniformLocation[uniformName];
        
        GLint uniformLocation = glGetUniformLocation(m_RendererId, uniformName.c_str());
        if(uniformLocation == -1){
            LOG_ERR("[Invalid Uniform] " + uniformName, "", 3);
        }
        m_UniformLocation[uniformName] = uniformLocation;
        return uniformLocation;
    }
}