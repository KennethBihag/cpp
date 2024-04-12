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

void pfPermute()
{
    char permuteArgs[] = { 10,0,0,0,
        42, 87, 15, 61, 33,
        94, 20, 76, 50, 10 };
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

    fname = "permute_test";
    p = new Timfiler(pfPermute,p_unit::ms, fname);
    p->Run();
    p->PrintData();

    delete p;
    p = new Memfiler(pfPermute, p_unit::kb, fname);
    p->Run();
    p->PrintData();

    return EXIT_SUCCESS;
}