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
        GLShader(std::string_view text, const ShaderType type) : shaderText(text)
        {
            this->shaderText = text;
            this->id = glCreateShader(type);
            this->compile(this->shaderText.data());
        }
        
        GLShader(const GLShader&) = default;
        GLShader(GLShader&&) = default;
        
        ~GLShader()
        {
            if (this->id != 0)
            {
                glDeleteShader(this->id);
                this->id = 0;
            }
        }
        
        const std::string_view& get() const
        {
            return this->shaderText;
        }
        
        const GLuint get_id() const
        {
            return this->id;
        }

        const char* get_c_str() const
        {
            return this->shaderText.data();
        }
        
    private:
    
        void compile(const GLchar* text)
        {
            glShaderSource(this->id, 1, &text, nullptr);
            glCompileShader(this->id);
        }
        
    private:
        std::string_view shaderText;
        GLuint id = 0;
    };
}

#endif