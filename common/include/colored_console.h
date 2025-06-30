#ifndef COLORED_CONSOLE_H
#define COLORED_CONSOLE_H

#include <iostream>
#include <iomanip>

#include <windows.h>

enum class Console: int {
    BLK, BLU, GRN, CYN,RED, VLT, YLW, DFLT=7
};

inline const HANDLE g_OutConsole = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE g_LogConsole = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE g_ErrConsole = GetStdHandle(STD_ERROR_HANDLE);

#ifdef _WIN32
#ifdef EXP_BUILD
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif
#else
#define COMMON_API 
#endif

COMMON_API void ColoredConsole(Console c, std::ostream &out, const char*);
COMMON_API void SetConsoleColor(Console c, const HANDLE handle);


#endif