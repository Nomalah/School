#include <fstream>
#include <sstream>
#include <string>

#include "../../__nmlh_gen_include.h"
#include "nmlh_Shader.h"

namespace nmlh::util{
    const unsigned ShaderTypes = 2;

    Shader::Shader(const std::string& ShaderSource) : m_RendererId(glCreateProgram()){        
        std::ifstream ShaderFile(ShaderSource);

        if(!ShaderFile.is_open()){
            LOG_ERR("[Couldn't Open File] ", ShaderSource, 3);
            m_RendererId = 0;
            return;
        }

        std::stringstream Shaders[ShaderTypes];

        enum ShaderType{
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1,
            GEOMETRY = 2
        };
        
        ShaderType CurShader = ShaderType::NONE;

        std::string Line = "";
        while(getline(ShaderFile, Line)){
            if(Line.find("#Shader ") != std::string::npos){
                if(Line.find("vertex", 8) != std::string::npos)
                    CurShader = ShaderType::VERTEX;
                else if(Line.find("fragment", 8) != std::string::npos)
                    CurShader = ShaderType::FRAGMENT;
                else if(Line.find("geometry", 8) != std::string::npos)
                    CurShader = ShaderType::GEOMETRY;
            }else{
                if(CurShader != ShaderType::NONE){
                    Shaders[CurShader] << Line << '\n';
                }
            }
        }

        GLuint ShaderId[ShaderTypes];
        for(unsigned i = 0; i < ShaderTypes; i++){
            std::string Shader = Shaders[i].str();
            switch(i){
                case ShaderType::VERTEX:
                    ShaderId[i] = CompileShader(GL_VERTEX_SHADER, Shader);
                    break;
                case ShaderType::FRAGMENT:
                    ShaderId[i] = CompileShader(GL_FRAGMENT_SHADER, Shader);
                    break;
                case ShaderType::GEOMETRY:
                    ShaderId[i] = CompileShader(GL_GEOMETRY_SHADER, Shader);
            }
            glAttachShader(m_RendererId, ShaderId[i]);
        }
        glLinkProgram(m_RendererId);

        // Check if the program is a valid Shader
        GLint Successful;
        glValidateProgram(m_RendererId);
        glGetProgramiv(m_RendererId, GL_VALIDATE_STATUS, &Successful);
        if(Successful == GL_FALSE){
            int MessageLength = 0;
            glGetProgramiv(m_RendererId, GL_INFO_LOG_LENGTH, &MessageLength);
            char* ErrMessage = new char[MessageLength];
            if(ErrMessage == nullptr){
                LOG_ERR("[Alloc Fail] ", "char* ErrMessage = new char[MessageLength];", 3);
            }else{
                glGetProgramInfoLog(m_RendererId, MessageLength, &MessageLength, ErrMessage);
                LOG_ERR("[Shader Vallidation Failed] ", ErrMessage, 2);
            }

            m_RendererId = 0;
        }
        
        for(unsigned i = 0; i < ShaderTypes; i++){
            glDeleteShader(ShaderId[i]);
        }
    }

    GLuint Shader::CompileShader(GLenum type, const std::string& source){
        GLuint ShaderId = glCreateShader(type);
        const char* ShaderSrc = source.c_str();

        glShaderSource(ShaderId, 1, &ShaderSrc, nullptr);
        glCompileShader(ShaderId);

        // Check if the compile was successful
        GLint Successful;
        glGetShaderiv(ShaderId, GL_COMPILE_STATUS, &Successful);
        if(Successful == GL_FALSE){
            int MessageLength = 0;
            glGetShaderiv(ShaderId, GL_INFO_LOG_LENGTH, &MessageLength);
            char* ErrMessage = new char[MessageLength];
            if(ErrMessage == nullptr){
                LOG_ERR("[Alloc Fail] ", "char* message = new char[messageLength];", 3);
            }else{
                glGetShaderInfoLog(ShaderId, MessageLength, &MessageLength, ErrMessage);
                LOG_ERR("[Shader Compilation Failed] ", ErrMessage, 2);
            }

            return 0;
        }
        
        return ShaderId;
    }

    GLint Shader::GetUniformLocation(const std::string& UniformName){
        if(m_UniformLocation.find(UniformName) != m_UniformLocation.end())
            return m_UniformLocation[UniformName];
        
        GLint UniformLocation = glGetUniformLocation(m_RendererId, UniformName.c_str());
        if(UniformLocation == -1){
            LOG_ERR("[Invalid Uniform] " + UniformName, "", 3);
        }
        m_UniformLocation[UniformName] = UniformLocation;
        return UniformLocation;
    }
}