#include "profiler.hpp"
#include "memfiler.hpp"
#include "timfiler.hpp"
#include "parallelfiler.hpp"

#include <string.h>
#include <unistd.h>

#include <iostream>
#include <vector>

#include "common/include/tests.h"

using namespace std;

int g_argc;
const char **g_argv;

void pfBubblesort()
{
    bubblesort_test(g_argc, g_argv);
}

void pfMergesort()
{
    mergesort_test(g_argc, g_argv);
}

void pfPermute2()
{
    char permuteArgs[] = { 2,0,0,0,
        42, 87};
    permute_test((void*)permuteArgs);
}

void pfPermute4()
{
    char permuteArgs[] = { 4,0,0,0,
        42, 87, 15, 61};
    permute_test((void*)permuteArgs);
}

void pfPermute8()
{
    char permuteArgs[] = { 8,0,0,0,
        42, 87, 15, 61, 33,
        94, 20, 76 };
    permute_test((void*)permuteArgs);
}

void pfPermute10()
{
    char permuteArgs[] = { 10,0,0,0,
        87, 33, 0, 1, 3,
        94, 40, 76, 69, 13};
    permute_test((void*)permuteArgs);
}

int main(int argc, const char *argv[])
{
    cout << "Profiling..." << endl;

    g_argc = 19;
    const char *nums[] = {
        "", "20", "-4", "7", "0", "1", "45", "-33", "-6", "99",
        "10", "-3", "77", "69", "13", "24", "-52", "-6", "99"};
    g_argv = nums;

    vector<Profiler*> profs;

    string fname("bubblesort_test");
    profs.push_back(new Timfiler(pfBubblesort, p_unit::ms, fname));
    profs.push_back(new Memfiler(pfBubblesort, p_unit::kb, fname));

    fname = "permute_test2";
    profs.push_back(new Timfiler(pfPermute2,p_unit::ms, fname));

    fname = "permute_test4";
    profs.push_back(new Timfiler(pfPermute4,p_unit::ms, fname));

    fname = "permute_test8";
    profs.push_back(new Timfiler(pfPermute8,p_unit::ms, fname));

    fname = "permute_test10";
    profs.push_back(new Timfiler(pfPermute10,p_unit::ms, fname));

    Parallelfiler prfl(profs);
    prfl.ParallelRun();

    for(auto &p : profs)
        delete p;
    profs.clear();

    return EXIT_SUCCESS;
}