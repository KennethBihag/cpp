#include "timfiler.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;

void Timfiler::PrintData()
{
    std::ios state(0);
    state.copyfmt(cout);
    cout << "Time ran for " << _funcName << " at 0x" << std::hex
         << std::uppercase << std::setfill('0')
         << (unsigned long long)_func << std::dec << " is about "
         << measurement << (p_unit::s == _unit ?
            " seconds." : " milliseconds.") << endl;
    cout.copyfmt(state);
}

void Timfiler::Run()
{
    cout << "Timing run time of " << _funcName << endl;

    redirectOut(voidBuffer);
    auto start = std::chrono::high_resolution_clock::now();
    _func();
    auto end = std::chrono::high_resolution_clock::now();
    restoreOut();

    if(_unit == p_unit::s)
        measurement =
            std::chrono::duration_cast<std::chrono::seconds>(
                end - start).count();
    else
        measurement =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start).count();
}
