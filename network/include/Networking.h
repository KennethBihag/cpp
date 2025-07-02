#ifndef NETWORKING_H
#define NETWORKING_H

#ifdef _WIN32

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#define ISVLDSCKT(s) ((s) != INVALID_SOCKET)
#define GETSCKERR() (WSAGetLastError())
#define CLOSESKT(s) closesocket(s)
#define GETSYSERROR() (GetLastError())

int StartUp(WSADATA&);

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
#define GETSYSERROR() (errno)
typedef int SOCKET;

int StartUp();

#endif // _WIN32

#include <sstream>
#include <unordered_map>

#ifndef AI_ALL
#define AI_ALL 0x100
#endif

void CleanUp();
void ThrowError(const std::string&, int) noexcept(false);
void ThrowNetworkError(const std::string&) noexcept(false);
std::stringstream FileAsSStream(const char*);
extern std::unordered_map<int, std::string> g_familyMap;
extern std::unordered_map<int, std::string> g_sockMap;
extern std::unordered_map<int, std::string> g_protoMap;
extern std::unordered_map<int, std::string> g_flagMap;
inline const int g_rcvLim = 1024;

#endif