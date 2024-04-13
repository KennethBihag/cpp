#include "parallelfiler.hpp"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>

#ifndef _WIN32
char voidBuffer[32] = "/dev/null";
#else
char voidBuffer[32] = "NUL:";
#endif

using std::cout;
using std::endl;
using std::ofstream;
using std::streambuf;
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
    cout << "Synchronous run" << endl;
#ifndef NO_COUT_RDIR
    auto orgBuffer = cout.rdbuf();
    ofstream newFstream(voidBuffer);
    cout.rdbuf(newFstream.rdbuf());
#endif   
    redirectOut(voidBuffer);
    vector<Profiler *> &profs = *_profilers;
    for (auto &p : profs)
        p->Run();
    restoreOut();
#ifndef NO_COUT_RDIR
    cout.flush();
    cout.rdbuf(orgBuffer);
    newFstream.close();
#endif
    for (auto &p : profs)
        p->PrintData();
}

void Parallelfiler::ParallelRun()
{
    cout << "Asynchronous run" << endl;
#ifndef NO_COUT_RDIR
    auto orgBuffer = cout.rdbuf();
    ofstream newFstream(voidBuffer);
    cout.rdbuf(newFstream.rdbuf());
#endif
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
#ifndef NO_COUT_RDIR
    cout.flush();
    cout.rdbuf(orgBuffer);
    newFstream.close();
#endif
    for(auto &p : *_profilers)
        p->PrintData();
}