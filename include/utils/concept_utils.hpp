#pragma once

#include <concepts>



namespace utils
{
    template<class T, class Base>
    concept Extends = std::is_base_of<Base, T>::value;
}