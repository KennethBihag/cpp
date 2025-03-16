#ifndef INCLUDES_HPP
#define INCLUDES_HPP

#if defined(_WIN32)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#define ISVLDSCKT(s) ((s) != INVALID_SOCKET)
#define GETSCKERR() (WSAGetLastError())

#else

#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>

#define ISVLDSCKT(s) ((s) >= 0)
#define GETSCKERR() (errno)
typedef int SOCKET;

#endif

namespace other{
    void PrintIP(addrinfo *);
};

#endif