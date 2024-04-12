#include "parallelfiler.hpp"

#include <pthread.h>

#include "timfiler.hpp"

using std::vector;

void Parallelfiler::Run()
{
    vector<Profiler *> &profs = *_profilers;
    for (auto &p : profs)
        p->Run();
    for (auto &p : profs)
        p->PrintData();
}


void *RunProfiler(void *arg)
{
    Profiler *p = reinterpret_cast<Profiler*>(arg);
    p->Run();
    return (void*)0;
}

void Parallelfiler::ParallelRun()
{
    vector<pthread_t> ths;

    for(auto &p : *_profilers)
    {
        ths.push_back(0);
        pthread_create(&ths.back(), NULL, RunProfiler,
                       reinterpret_cast<void*>(p));
    }

    for(auto &t : ths){
        pthread_join(t,NULL);
    }

    for(auto &p : *_profilers)
        p->PrintData();

    return;
}