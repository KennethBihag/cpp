#include "common.hpp"

int GetStreamSize(std::iostream &strm){
    auto b = strm.tellg();
#ifndef _WINDOWS
    strm.seekg(0, std::ios_base::seekdir(2));
#else
    strm.seekg(0, std::ios_base::_Seekend);
#endif
    auto e = strm.tellg();
    strm.seekg(b);
    return e-b;
}