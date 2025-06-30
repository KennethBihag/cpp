#include "colored_console.h"

#include <exception>
#include <sstream>
#include <string>

struct COMMON_API Logger {
    enum LogType {Inf, Out, Err};
    static void Log(LogType, const std::string&, const std::string&);
    static void Log(const std::exception&);
};
