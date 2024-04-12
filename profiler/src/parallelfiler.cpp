#include "parallelfiler.hpp"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#ifndef _WIN32
char voidBuffer[32] = "/dev/null";
#else
char voidBuffer[32] = "NUL:";
#endif

using std::vector;

void *RunProfiler(void *arg)
{
    Profiler *p = (Profiler*)(arg);
    p->Run();
    return (void*)0;
}

void Parallelfiler::redirectOut(const char* const file)
{
    rdfd = dup(STDOUT_FILENO);
    freopen(file, "w", stdout);
}

void Parallelfiler::restoreOut()
{
    printf("\n");
    fflush(stdout);
    dup2(rdfd, STDOUT_FILENO);
    close(rdfd);
}

void Parallelfiler::Run()
{
    std::cout << "Synchronous run\n";
    redirectOut(voidBuffer);
    vector<Profiler *> &profs = *_profilers;
    for (auto &p : profs)
        p->Run();
    restoreOut();
    for (auto &p : profs)
        p->PrintData();
}

void Parallelfiler::ParallelRun()
{
    std::cout << "Asynchronous run\n";
    redirectOut(voidBuffer);
    vector<pthread_t> ths;
    for(auto &p : *_profilers)
    {
        ths.push_back(0);
        pthread_create(&ths.back(), NULL, RunProfiler, (void*)(p));
    }
    for(auto &t : ths)
        pthread_join(t,NULL);
    restoreOut();
    for(auto &p : *_profilers)
        p->PrintData();
}