#include "perfiler.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void Perfiler::AddFunction(
        std::string& funcName, func_t function, void *args)
{
    _functions[funcName] =
        make_tuple(function, args, 0LL);
}

void Perfiler::ProfileTime(string key)
{
    cout << "PROFILING " << key << endl;
    auto start = std::chrono::high_resolution_clock::now();
    get<0>(_functions[key])( get<1>(_functions[key]) );
    auto end = std::chrono::high_resolution_clock::now();
    cout << "DONE" << endl;
    get<2>(_functions[key]) =
        std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start).count();
}

void Perfiler::Run()
{
    for(auto &f : _functions)
        ProfileTime(f.first);
}


void Perfiler::ParallelRun()
{
    std::vector<std::thread> threads;

    for (auto &f : _functions)
        threads.emplace_back(
            [this, f](){
                ProfileTime(f.first);
        });

    for (auto &t : threads)
    {
        t.join();
    }
}

void Perfiler::PrintData(string key)
{
    std::ios state(0);
    state.copyfmt(cout);

    cout << "Time ran for " << key << " at 0x" << std::hex
         << std::uppercase << std::setfill('0')
         << (unsigned long long)get<0>(_functions[key])
         << std::dec << " is about "
         << get<2>(_functions[key]) << " milliseconds." << endl;

    cout.copyfmt(state);
}

void Perfiler::PrintData()
{
    for(auto &f : _functions)
        PrintData(f.first);
}