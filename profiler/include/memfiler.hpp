#ifndef MEMFILER_HPP
#define MEMFILER_HPP

#include <string>

#include "profiler.hpp"

class Memfiler : public Profiler
{
public:
    Memfiler(void (*func)(), p_unit unit, std::string &fname) :
        Profiler(func, unit, fname) {}
    void PrintData() override;
    void Run() override;
};

#endif // MEMFILER_HPP