#ifndef COMMON_H
#define COMMON_H

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#ifndef AI_ALL
#define AI_ALL 0x100
#endif

#endif