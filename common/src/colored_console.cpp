#include "colored_console.h"

#include <windows.h>

using std::ostream;

void ColoredConsole(Console c, ostream &out, const char *msg){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (int)c);
    out << msg;
    SetConsoleTextAttribute(hConsole, int(Console::DFLT));
} 