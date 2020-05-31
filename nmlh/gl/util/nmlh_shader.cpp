#include <fstream>
#include <sstream>
#include <string>


#include "../../nmlh_log.hpp"
#include "nmlh_shader.h"

namespace nmlh::gl::util{
    const unsigned shaderTypes = 3;

    shader::shader(const std::string& shaderSource) : m_RendererId(glCreateProgram()){
        std::ifstream shaderFile(shaderSource);

        std::stringstream shaders[shaderTypes];

        enum shaderType{
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
            GEOMETRY = 2,
        };
        
        shaderType curShader = shaderType::NONE;

        std::string line = "";
        while(getline(std::cin, line)){
            if(line.find("#shader ") != std::string::npos){
                if(line.find("vertex", 8) != std::string::npos)
                    curShader = shaderType::VERTEX;
                else if(line.find("fragment", 8) != std::string::npos)
                    curShader = shaderType::FRAGMENT;
                else if(line.find("geometry", 8) != std::string::npos)
                    curShader = shaderType::GEOMETRY;
            }else{
                if(curShader != shaderType::NONE)
                    shaders[curShader] << line;
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

        for(unsigned i = 0; i < shaderTypes; i++)
            glDeleteShader(shaderId[i]);
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
            glGetShaderiv(m_RendererId, GL_INFO_LOG_LENGTH, &messageLength);

            char* errMessage = new char[messageLength];
            if(errMessage == nullptr){
                LOG_ERR("[Alloc Fail] ", "char* message = new char[messageLength];", 3);
            }else{
                glGetShaderInfoLog(m_RendererId, messageLength, &messageLength, errMessage);
                LOG_ERR("[Shader Vallidation Failed] ", errMessage, 2);
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