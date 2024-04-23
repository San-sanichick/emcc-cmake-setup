#pragma once

#include <string>


#ifdef __EMSCRIPTEN__

namespace gl 
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class GLShader
    {
    private:
        std::string shaderText;
    public:
        GLShader(std::string text) : shaderText(text)
        {}
        
        GLShader(const char text[]) : shaderText(text)
        {}

        std::string& get()
        {
            return this->shaderText;
        }

        const char* get_c_str()
        {
            return this->shaderText.c_str();
        }
    };
}

#endif