#include "common.hpp"

int GetStreamSize(std::iostream &strm){
    auto b = strm.tellg();
    strm.seekg(0, std::ios_base::seekdir::_S_end);
    auto e = strm.tellg();
    strm.seekg(b);
    return e-b;
}