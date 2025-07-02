#ifndef COLORED_CONSOLE_HPP
#define COLORED_CONSOLE_HPP

#include <iostream>
#include <iomanip>

#ifdef _WIN32
#include "exports.hpp"
#include <windows.h>

#else

#define COLOR(c) "\x1b[3" #c "m"
using HANDLE = int;
using Console = const char*;
#endif // _WIN32


#ifdef _WIN32
enum class Console: int {
    BLK, BLU, GRN, CYN,RED, VLT, YLW, DFLT=7
};

inline const HANDLE g_OutConsole = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE g_LogConsole = GetStdHandle(STD_OUTPUT_HANDLE);
inline const HANDLE g_ErrConsole = GetStdHandle(STD_ERROR_HANDLE);

COMMON_API void SetConsoleColor(Console c, const HANDLE handle);
#else
inline const char *const BLK = COLOR(0);
inline const char *const BLU = COLOR(4);
inline const char *const GRN = COLOR(2);
inline const char *const CYN = COLOR(6);
inline const char *const RED = COLOR(1);
inline const char *const VLT = COLOR(5);
inline const char *const YLW = COLOR(3);
inline const char *const DFLT = "\x1b[0m";
#endif // _WIN32

COMMON_API void ColoredConsole(Console c, std::ostream &out, const char*);

#endif