#include "gl/shader.hpp"


gl::GLShader::GLShader(std::string_view text, const ShaderType type) : shaderText(text)
{
    this->shaderText = text;
    this->id = glCreateShader(type);
    this->compile(this->shaderText.data());
}

gl::GLShader::~GLShader()
{
    if (this->id != 0)
    {
        glDeleteShader(this->id);
        this->id = 0;
    }
}



const std::string_view& gl::GLShader::get() const
{
    return this->shaderText;
}

uint32_t gl::GLShader::get_id() const
{
    return this->id;
}

const char* gl::GLShader::get_c_str() const
{
    return this->shaderText.data();
}



void gl::GLShader::compile(const GLchar* text)
{
    glShaderSource(this->id, 1, &text, nullptr);
    glCompileShader(this->id);
}