#pragma once


#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <string_view>

namespace gl 
{
    enum ShaderType
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER
    };

    class GLShader
    {
    public:
        GLShader(std::string_view text, const ShaderType type);
        GLShader(const GLShader&) = default;
        GLShader(GLShader&&) = default;
        ~GLShader();
        
        
        const std::string_view& get() const;
        GLuint get_id() const;
        const char* get_c_str() const;
        
    private:
        void compile(const GLchar* text);
        
    private:
        std::string_view shaderText;
        GLuint id = 0;
    };
}

#endif