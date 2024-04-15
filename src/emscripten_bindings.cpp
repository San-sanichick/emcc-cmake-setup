#include <emscripten/bind.h>
// #include <emscripten/val.h>
#include <iostream>
#include "dyn_array_wrapper.hpp"
// #include "timer.hpp"

// #include <Logger.h>
// #include <result.hpp>
// #include "debug.hpp"
// #include "vec2/vec2.hpp"

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

void getBuffer_(const emsc::val &v)
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


EMSCRIPTEN_BINDINGS(math)
{
    emsc::function("getBuffer", &getBuffer);
    emsc::function("getBuffer_", &getBuffer_);
}