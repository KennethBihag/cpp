#ifndef PERFILER_HPP
#define PERFILER_HPP

#include <string>
#include <map>

typedef void(*func_t)(void*);

class Perfiler
{
    std::map<std::string,std::tuple<func_t, void*, long long>>
        _functions;

    void ProfileTime(std::string key);
    void PrintData(std::string key);

public:
    void AddFunction(
        std::string& funcName, func_t, void *args);
    void Run();
    void ParallelRun();
    void PrintData();
};

#endif