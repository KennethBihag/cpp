#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "colored_console.hpp"

#include <exception>
#include <string>

struct COMMON_API Logger {
    enum LogType {Inf, Out, Err};
    static void Log(LogType, const std::string&, const std::string&);
    static void Log(const std::exception&);
};

#endif