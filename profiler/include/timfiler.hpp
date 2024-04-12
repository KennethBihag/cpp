#ifndef TIMFILER_HPP
#define TIMFILER_HPP

#include "profiler.hpp"

#include <string>

class Timfiler : public Profiler
{
public:
    Timfiler(void (*func)(), p_unit unit, std::string &fname) :
        Profiler(func, unit, fname) {}
    void PrintData() override;
    void Run() override;
};

#endif // TIMFILER_HPP