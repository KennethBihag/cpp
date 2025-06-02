#ifndef NETWORKING_H
#define NETWORKING_H
#if defined(_WIN32)

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#define ISVLDSCKT(s) ((s) != INVALID_SOCKET)
#define GETSCKERR() (WSAGetLastError())
#define CLOSESKT(s) closesocket(s)

int StartUp(WSADATA&);

inline void CleanUp(PIP_ADAPTER_ADDRESSES adapters){
    free(adapters);
    WSACleanup();
}

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
#define CLOSESKT(s) close(s)
typedef int SOCKET;

int StartUp();

#endif // _WIN32

#include <iostream>

#ifndef AI_ALL
#define AI_ALL 0x100
#endif

void CleanUp();
void Break(std::ostream&);

#endif