#include "gl/canvas.hpp"
// #include"debug.hpp"

#ifdef __EMSCRIPTEN__


gl::Canvas::Canvas(uint32_t id, int32_t w, int32_t h)
{
    this->vb = id;
    this->ctx = id;
    
    this->w = w;
    this->h = h;

    gl::GLShader vertSh(
        "#version 300 es\n"
        "layout (location = 0) in vec3 position;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
        "}",
        gl::VERTEX
    );

    gl::GLShader fragSh(
        "#version 300 es\n"
        "precision mediump float;\n"
        "out vec4 color;\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
        "}",
        gl::FRAGMENT
    );

    this->program = new gl::GLProgram("test", { vertSh, fragSh });


    auto interface = GrGLInterfaces::MakeWebGL();
    auto context = GrDirectContexts::MakeGL();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0, 0, 0, 0);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    context->resetContext(kRenderTarget_GrGLBackendState | kMisc_GrGLBackendState);
    
    GrGLFramebufferInfo info;
    info.fFBOID = 0;

    auto colorSpace = SkColorSpace::MakeSRGB();
    const auto colorSettings = ColorSettings(colorSpace);
    info.fFormat = colorSettings.pixFormat;
    
    GrGLint sampleCount;
    GrGLint stencil;

    glGetIntegerv(GL_SAMPLES, &sampleCount);
    glGetIntegerv(GL_STENCIL_BITS, &stencil);

    auto target = GrBackendRenderTargets::MakeGL(w, h, sampleCount, stencil, info);
    
    this->surface = SkSurfaces::WrapBackendRenderTarget(
        context.get(),
        target,
        kBottomLeft_GrSurfaceOrigin,
        colorSettings.colorType,
        colorSpace,
        nullptr
    );
}


gl::Canvas::~Canvas()
{
    delete this->program;
}

// https://groups.google.com/g/skia-discuss/c/P4GO92rxIaM
void gl::Canvas::render(GLfloat r, GLfloat g, GLfloat b)
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
        glUseProgram(this->program->get_id());
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        SkPaint p;
        p.setAntiAlias(true);
        p.setColor(SK_ColorCYAN);
        auto canvas = this->surface->getCanvas();
        canvas->drawCircle({ this->w / 2.0f, this->h / 2.0f }, 20, p);
    }

    glDeleteBuffers(1, &VBO);
}

#endif