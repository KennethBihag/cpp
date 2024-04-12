#ifndef PARALLELFILER_HPP
#define PARALLELFILER_HPP

#include <vector>

#include "profiler.hpp"

extern char voidBuffer[32];

class Parallelfiler
{
    int rdfd;
    std::vector<Profiler *> *_profilers;

    void redirectOut(const char* const file);
    void restoreOut();
public:

    Parallelfiler(std::vector<Profiler *> &profilers)
        : _profilers(&profilers) {}
    void Run();
    void ParallelRun();

};

#endif // PARALLELFILER_HPP
