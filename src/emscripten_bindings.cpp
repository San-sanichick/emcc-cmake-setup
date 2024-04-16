#include <emscripten/bind.h>
#include <emscripten/html5.h>

#include <GLES2/gl2.h>

// #include <emscripten/val.h>
#include <iostream>
#include "dyn_array_wrapper.hpp"
// #include "timer.hpp"


namespace emsc = emscripten;

void getBuffer(const intptr_t data, size_t size)
{
    // Timer timer;
    const auto ptr = reinterpret_cast<uint8_t*>(data);

    utils::ReadonlyDynArrayWrapper buffer(ptr, size);
    
    for (auto el : buffer)
    {
        std::cout << unsigned(el) << ' ';
    }
    std::cout << std::endl;
}

void getBufferVector(const emsc::val &v)
{
    // Timer timer;
    std::vector<uint8_t> rv;
    const auto len = v["length"].as<unsigned>();
    rv.resize(len);

    emsc::val view(emsc::typed_memory_view(len, rv.data()));
    view.call<void>("set", v);

    for (auto el : rv)
    {
        std::cout << unsigned(el) << ' ';
    }
    std::cout << std::endl;
}




class Canvas
{
private:
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx;
    uint32_t programId;
    
    int32_t w, h;
    GLuint vb;

public:
    Canvas(uint32_t id, int32_t w, int32_t h)
    {
        // std::cout << 
        this->programId = id;
        this->vb = id;
        this->ctx = id;
        
        this->w = w;
        this->h = h;
    }
    
    ~Canvas()
    {
        emscripten_webgl_make_context_current(0);
    }

    // https://groups.google.com/g/skia-discuss/c/P4GO92rxIaM
    void render(GLfloat r, GLfloat g, GLfloat b)
    {
        // grab the context in case we lost it (we probably did)
        emscripten_webgl_make_context_current(this->ctx);

        glViewport(0, 0, this->w, this->h);
        glBindFramebuffer(GL_FRAMEBUFFER, vb);
        glDisable(GL_DEPTH_TEST);
        glClearColor(r, g, b, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};


EMSCRIPTEN_BINDINGS(math)
{
    emsc::function("getBuffer", &getBuffer);
    emsc::function("getBufferVector", &getBufferVector);
    
    emsc::class_<Canvas>("Canvas")
        .constructor<uint32_t, int32_t, int32_t>()
        .function("render", &Canvas::render);
}