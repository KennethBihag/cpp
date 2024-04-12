
#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <iostream>
#include <string>

extern const char *const voidBuffer;

enum p_unit
{
    ms, s, kb, mb
};

class Profiler
{
protected:

    std::string _funcName;
    void (*_func)();
    p_unit _unit;
    long long measurement;
    int rdfd;

    void redirectOut(const char* const file);
    void restoreOut();

public:

    Profiler(void (*func)(), p_unit unit, std::string &fname)
    {
        _func = func;
        _unit = unit;
        _funcName = fname;
    }

    virtual ~Profiler();
    virtual void PrintData() = 0;
    
    virtual void Run()
    {
        std::cout << "This profiler class' profiling function"
                     " is not yet implemented."
                  << std::endl;
    }
};

#endif // PROFILER_HPP
