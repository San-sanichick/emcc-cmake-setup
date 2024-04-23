#pragma once

#ifdef __EMSCRIPTEN__

#include <GLES3/gl3.h>
#include <string_view>
#include <vector>

#include "shader.hpp"


namespace gl 
{
    class GLProgram
    {
    public:
        GLProgram(std::string_view name, const std::initializer_list<gl::GLShader>& shaders)
        {
            this->id = glCreateProgram();
            
            this->shaders.reserve(shaders.size());

            for (auto& shader : shaders)
            {
                glAttachShader(this->id, shader.get_id());
                this->shaders.push_back(std::move(shader));
            }
            
            this->link();
        }

        ~GLProgram()
        {
            if (this->id != 0)
            {
                glDeleteProgram(0);
                this->id = 0;
            }
        }
        
        const GLuint get_id() const
        {
            return this->id;
        }

    private:
        std::string_view name;
        GLuint id = 0;
        
        std::vector<GLShader> shaders;
        

        void link()
        {
            glLinkProgram(this->id);
        }
    };
}


#endif

