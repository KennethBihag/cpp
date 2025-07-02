#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <iomanip>

#include "exports.hpp"

COMMON_API int GetStreamSize(std::iostream &strm);

template<typename T>
void PrintSize(){
    std::cout << std::left
              << std::setw(24) << typeid(T).name() << ":"
              << std::right
              << std::setw(4) << sizeof(T) << ":"
              << std::setw(4) << alignof(T)
              << std::endl;
}

#endif
