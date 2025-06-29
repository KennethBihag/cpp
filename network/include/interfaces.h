#ifndef INTERFACES_H
#define INTERFACES_H

#include "networking.h"

namespace Knt {
    struct Interfaces {
        static const std::string GetAddrInfo(const addrinfo*);
        static const std::string GetInterfaces();
        static std::string GetSockInfo(const sockaddr*, int);
    };
}

#endif