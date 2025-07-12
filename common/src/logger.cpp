#include "logger.hpp"

#include <sstream>

using std::string; using std::stringstream;
using std::cerr; using std::clog; using std::cout;

const string IndentBody(const string &body){
    stringstream formatted(string("\t"));
    for(auto beg = body.cbegin(); beg != body.cend(); ++beg){
        formatted << *beg;
        if(*beg == '\n')
            formatted << '\t';
    }

    return formatted.str();
}

COMMON_API void Logger::Log(LogType logType, const string &label, const string &body){
    stringstream logMsgStrm;
    logMsgStrm << label << ":\n\t";
    logMsgStrm << IndentBody(body);
    logMsgStrm << "\n";
    
    switch(logType){
    case LogType::Inf:
        ColoredConsole(Console::YLW, clog, logMsgStrm.str().c_str());
    break;
    case LogType::Out:
        ColoredConsole(Console::GRN, cout, logMsgStrm.str().c_str());
    break;
    case LogType::Err:
        ColoredConsole(Console::RED, cerr, logMsgStrm.str().c_str());
    break;
    }
}

void Logger::Log(const std::exception& ex){
    SetConsoleColor(Console::RED, g_ErrConsole);
    cerr << ex.what() << "\n";
    SetConsoleColor(Console::DFLT, g_ErrConsole);
}