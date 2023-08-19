#pragma once

#include "../../__nmlh_gen_include.h"
#include <string>
#include <unordered_map>

namespace nmlh::util{
    class Shader{
        private:
            GLuint m_RendererId;
            std::unordered_map<std::string, GLuint> m_UniformLocation;
            
            GLint GetUniformLocation(const std::string& UniformName);
            GLuint CompileShader(GLenum Type, const std::string& Source);
        public:
            // Constructor creates a shader from a GLSL file
            Shader(const std::string& shaderSource);
            ~Shader(){
                glUseProgram(0);
                glDeleteProgram(m_RendererId);
            }

            GLuint GetId(){return m_RendererId;}
            void Bind() const{glUseProgram(m_RendererId);}
            void UnBind() const{glUseProgram(0);}


            void SetUniform1i(const std::string& UniformName, glm::vec<1, int, glm::defaultp> UniformValues){
                glUniform1iv(GetUniformLocation(UniformName), 1, &UniformValues[0]);
            }
            
            void SetUniform4f(const std::string& UniformName, glm::vec4 UniformValues){
                glUniform4fv(GetUniformLocation(UniformName), 1, &UniformValues[0]);
            }

            void SetUniformMatrix4fv(const std::string& UniformName, glm::mat4 UniformValues){
                glUniformMatrix4fv(GetUniformLocation(UniformName), 1, GL_FALSE, &UniformValues[0][0]);
            }


        private:
            // Disallow Copy & move semantics with shaders
            Shader(const Shader&);
            Shader(Shader&&);
            Shader& operator=(const Shader&);
            Shader& operator=(Shader&&);
    }; 
}