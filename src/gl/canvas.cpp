#include "gl/canvas.hpp"

Canvas::Canvas(uint32_t id, int32_t w, int32_t h)
{
    this->programId = glCreateProgram();
    
    this->vb = id;
    this->ctx = id;
    
    this->w = w;
    this->h = h;
    this->vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertSh, NULL);
    glCompileShader(vShader);
    

    this->fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fracSh, NULL);
    glCompileShader(fShader);
    
    glAttachShader(this->programId, vShader);
    glAttachShader(this->programId, fShader);
    glLinkProgram(this->programId);
}


Canvas::~Canvas()
{
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    glDeleteProgram(this->programId);
    
    delete[] vertSh;
    delete[] fracSh;
}

// https://groups.google.com/g/skia-discuss/c/P4GO92rxIaM
void Canvas::render(GLfloat r, GLfloat g, GLfloat b)
{
    glViewport(0, 0, this->w, this->h);
    glDisable(GL_DEPTH_TEST);
    
    static const GLfloat vBuffer[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    GLuint VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vBuffer), vBuffer, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    {
        glClearColor(r, g, b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(this->programId);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    glDeleteBuffers(1, &VBO);
}
