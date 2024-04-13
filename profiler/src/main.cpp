#include "timfiler.hpp"
#include "parallelfiler.hpp"

#include <string.h>
#include <unistd.h>

#include <iostream>
#include <random>
#include <vector>

#include "common/include/sort.h"
#include "common/include/common.h"

using namespace std;

int o[16384];

void sleepy()
{
    int s = 3;
    printf("I am sleeping for %d seconds.\n", s);
    fflush(stdout);
    cout << "zzz zzzz zzz" << endl;
    sleep(s);
    printf("Just woke up!\n");
    fflush(stdout);
    cout << "???" << endl;
}

void sorting()
{
    int *copied = bubblesort_int(o, std::size(o), 1);
    cout << "ORIG: " << endl;
    print_intarr_elems(o, 52);
    cout << "NEW: " << endl;
    print_intarr_elems(copied, 52);
    free(copied);
}

int main(int argc, const char *argv[])
{
    cout << "Profiling..." << endl;
    // snprintf(voidBuffer, sizeof(voidBuffer), "data/profile.txt");
    int offset = std::size(o) / 2;
    for (int i = 0; i < std::size(o); i++)
    {
        int r = rand() % (offset + 1);
        int s = rand() % (offset + 1);
        o[i] = r - s;
    }

    vector<Profiler *> profs;

    string fname;
    fname = "sleepy1";
    profs.push_back(new Timfiler(sleepy, p_unit::ms, fname));
    fname = "sleepy2";
    profs.push_back(new Timfiler(sleepy, p_unit::ms, fname));
    fname = "sleepy3";
    profs.push_back(new Timfiler(sleepy, p_unit::ms, fname));

    fname = "sorting1";
    profs.push_back(new Timfiler(sorting, p_unit::ms, fname));

    fname = "sorting2";
    profs.push_back(new Timfiler(sorting, p_unit::ms, fname));

    fname = "sorting3";
    profs.push_back(new Timfiler(sorting, p_unit::ms, fname));

    Parallelfiler prfl(profs);
    prfl.ParallelRun();

    for (auto &p : profs)
        delete p;
    profs.clear();

    return EXIT_SUCCESS;
}