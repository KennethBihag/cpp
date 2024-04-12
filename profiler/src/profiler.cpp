#include "profiler.hpp"

#include <stdio.h>
#include <unistd.h>
#ifndef _WIN32
#include <fcntl.h>
#endif

#ifndef _WIN32
const char* const voidBuffer = "/dev/null";
#else
const char* const voidBuffer = "NUL:";
#endif

void Profiler::redirectOut(const char* const file)
{
    rdfd = dup(STDOUT_FILENO);
    freopen(file, "w", stdout);
}

void Profiler::restoreOut()
{
    printf("\n");
    fflush(stdout);
    dup2(rdfd, STDOUT_FILENO);
    close(rdfd);
}

Profiler::~Profiler()
{
#ifndef _WIN32
    int flags = fcntl(rdfd, F_GETFL);
    if (flags != -1 && flags != 0)
    {
        fprintf(stderr, "Forgot to close fd\n");
        fflush(stderr);
        close(rdfd);
    }
#endif
}