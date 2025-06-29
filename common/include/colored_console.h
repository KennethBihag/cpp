#ifndef COLORED_CONSOLE_H
#define COLORED_CONSOLE_H

#include <iostream>
#include <iomanip>

enum class Console: int {
    BLK, BLU, GRN, CYN,RED, DFLT=7
};

#ifdef EXP_BUILD
__declspec(dllexport)
#else
__declspec(dllimport)
#endif
void ColoredConsole(Console c, std::ostream &out, const char*);


#endif