#pragma once

#include "../../__nmlh_gen_include.h"
#include <string>
#include <unordered_map>

namespace nmlh::gl::util{
    class shader{
        private:
            GLuint m_RendererId;
            std::unordered_map<std::string, GLuint> m_UniformLocation;
            
            GLint getUniformLocation(const std::string& uniformName);
            GLuint compileShader(GLenum type, const std::string& source);
        public:
            // Constructor creates a shader from a GLSL file
            shader(const std::string& shaderSource);
            ~shader(){
                glUseProgram(0);
                glDeleteProgram(m_RendererId);
            }

            GLuint get_id(){return m_RendererId;};
            void bind() const{glUseProgram(m_RendererId);};
            void unbind() const{glUseProgram(0);};


            void setUniform1i(const std::string& uniformName, glm::vec<1, int, glm::defaultp> uniformValues){
                glUniform1iv(getUniformLocation(uniformName), 1, &uniformValues[0]);
            };
            
            void setUniform4f(const std::string& uniformName, glm::vec4 uniformValues){
                glUniform4fv(getUniformLocation(uniformName), 1, &uniformValues[0]);
            };

            void setUniformMatrix4fv(const std::string& uniformName, glm::mat4 uniformValues){
                glUniformMatrix4fv(getUniformLocation(uniformName), 1, GL_FALSE, &uniformValues[0][0]);
            };


        private:
            // Disallow Copy & move semantics with shaders
            shader(const shader&);
            shader(shader&&);
            shader& operator=(const shader&);
            shader& operator=(shader&&);
    }; 
}