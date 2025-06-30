#include "colored_console.h"

void ColoredConsole(Console c, std::ostream &out, const char *msg){
    SetConsoleColor(c, g_OutConsole);
    out << msg;
    SetConsoleColor(Console::DFLT, g_OutConsole);
} 

void SetConsoleColor(Console c, const HANDLE handle){
    SetConsoleTextAttribute(handle, (int)c);
}