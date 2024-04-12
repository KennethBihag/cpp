#ifndef PARALLELFILER_HPP
#define PARALLELFILER_HPP

#include <vector>

#include "profiler.hpp"

class Parallelfiler
{

    std::vector<Profiler *> *_profilers;

public:

    Parallelfiler(std::vector<Profiler *> &profilers)
        : _profilers(&profilers) {}
    void Run();
    void ParallelRun();

};

#endif // PARALLELFILER_HPP
