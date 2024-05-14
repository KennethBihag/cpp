#include <string.h>
#include <unistd.h>

#include <iostream>
#include <random>
#include <vector>

#include "common/include/sort.h"
#include "common/include/common.h"
#include "leetcode/include/test.hpp"

#include "timfiler.hpp"
#include "parallelfiler.hpp"
#include "perfiler.hpp"

using namespace std;


#ifndef PROFILE_LEETCODE
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
#endif // PROFILE_LEETCODE

int main(int argc, const char *argv[])
{
    cout << "Profiling..." << endl;
    // snprintf(voidBuffer, sizeof(voidBuffer), "data/profile.txt");
    string fname;
#ifndef STD_THREAD
    vector<Profiler *> profs;
#ifndef PROFILE_LEETCODE
    int offset = std::size(o) / 2;
    for (int i = 0; i < std::size(o); i++)
    {
        int r = rand() % (offset + 1);
        int s = rand() % (offset + 1);
        o[i] = r - s;
    }

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
#else
    fname = "DeckRevealedIncreasing";
    profs.push_back(new Timfiler((void(*)())DeckRevealedIncreasingTest, p_unit::ms, fname));
    fname = "Maximal Rectangle";
    profs.push_back(new Timfiler((void(*)())MaximalRectangleTest, p_unit::ms, fname));
    fname = "FindAllPeople";
    profs.push_back(new Timfiler((void(*)())FindAllPeopleTest, p_unit::ms, fname));
    fname = "HouseRobber";
    profs.push_back(new Timfiler((void(*)())HouseRobberTest, p_unit::ms, fname));
#endif // PROFILE_LEETCODE

    Parallelfiler prfl(profs);
    prfl.ParallelRun();

    for (auto &p : profs)
        delete p;
    profs.clear();
#else
    Perfiler perfiler;

    fname = "DeckRevealedIncreasing";
    perfiler.AddFunction(fname, (func_t)DeckRevealedIncreasingTest,0);
    fname = "FindAllPeople";
    perfiler.AddFunction(fname, (func_t)FindAllPeopleTest,0);
    fname = "Maximal Rectangle";
    perfiler.AddFunction(fname, (func_t)MaximalRectangleTest,0);
    fname = "HouseRobber";
    perfiler.AddFunction(fname, (func_t)HouseRobberTest,0);

    perfiler.ParallelRun();
    perfiler.PrintData();
#endif // STD_THREAD

    return EXIT_SUCCESS;
}