#ifdef __EMSCRIPTEN__
#include "gl/program.hpp"
#include <iostream>



gl::GLProgram::GLProgram(std::string_view name, const std::initializer_list<gl::GLShader>& shaders)
    : name(name)
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

gl::GLProgram::GLProgram(std::string_view name)
    : name(name)
{
    this->id = glCreateProgram();
    this->link();
}


gl::GLProgram::~GLProgram()
{
    if (this->id != 0)
    {
        glDeleteProgram(0);
        this->id = 0;
    }
}

void gl::GLProgram::link() const
{
    glLinkProgram(this->id);
}

#endif