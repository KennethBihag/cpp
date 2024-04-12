#include "memfiler.hpp"

#ifndef _WIN32
#include <sys/resource.h>
#endif

#include <iomanip>
#include <iostream>

#include "profiler.hpp"

using std::cout;
using std::endl;

void Memfiler::PrintData()
{
    std::ios state(0);
    state.copyfmt(cout);
    cout << "Memory used by " << _funcName << " at 0x" << std::hex 
         << std::uppercase << std::setfill('0')
         << (unsigned long long)_func << std::dec << " is about "
         << measurement << (p_unit::mb == _unit ? " Mb." : " Kb.")
         << endl;
    cout.copyfmt(state);
}

void Memfiler::Run()
{
#ifndef _WIN32
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    long startMem = ru.ru_maxrss;
    cout << "Start mem: " << startMem << endl;
#endif
    _func();
#ifndef _WIN32
    getrusage(RUSAGE_SELF, &ru);
    long endMem = ru.ru_maxrss;
    cout << "End mem: " << endMem << endl;
    measurement = endMem - startMem;
    if(_unit == p_unit::mb)
        measurement /= 1024;
#endif
}