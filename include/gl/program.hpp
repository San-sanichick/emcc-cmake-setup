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
        GLProgram(std::string_view name, const std::initializer_list<gl::GLShader>& shaders);
        ~GLProgram();
        
        const GLuint get_id() const { return this->id; }

    private:
        void link() const;
        
    private:
        std::string_view name;
        GLuint id = 0;
        
        std::vector<GLShader> shaders;
    };
}

#endif
