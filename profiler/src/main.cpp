#include <iostream>

#include "profiler.hpp"
#include "memfiler.hpp"
#include "timfiler.hpp"

#include <unistd.h>

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

    string fname("bubblesort_test");
    Profiler *p = new Timfiler(pfBubblesort, p_unit::ms, fname);
    p->Run();
    p->PrintData();
    delete p;

    p = new Memfiler(pfBubblesort, p_unit::kb, fname);
    p->Run();
    p->PrintData();
    delete p;

    fname = "permute_test2";
    p = new Timfiler(pfPermute2,p_unit::ms, fname);
    p->Run();
    p->PrintData();
    delete p;

    fname = "permute_test4";
    p = new Timfiler(pfPermute4,p_unit::ms, fname);
    p->Run();
    p->PrintData();

    fname = "permute_test8";
    p = new Timfiler(pfPermute8,p_unit::ms, fname);
    p->Run();
    p->PrintData();
    delete p;

    fname = "permute_test10";
    p = new Timfiler(pfPermute10,p_unit::ms, fname);
    p->Run();
    p->PrintData();

    return EXIT_SUCCESS;
}