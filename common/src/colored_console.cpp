#include "colored_console.hpp"


COMMON_API void ColoredConsole(Console c, std::ostream &out, const char *msg){
#ifdef _WIN32
    SetConsoleColor(c, g_OutConsole);
    out << msg;
    SetConsoleColor(Console::DFLT, g_OutConsole);
#else
    out << c << msg << DFLT;
#endif
} 

#ifdef _WIN32
void SetConsoleColor(Console c, const HANDLE handle){
    SetConsoleTextAttribute(handle, (int)c);
}
#endif