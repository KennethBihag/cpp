#ifndef NETWORKING_H
#define NETWORKING_H

#include <string>
#include <ostream>
#include <unordered_map>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#ifndef AI_ALL
#define AI_ALL 0x100
#endif

extern std::unordered_map<int, const std::string> g_familyMap;
extern std::unordered_map<int, const std::string> g_sockMap;
extern std::unordered_map<int, const std::string> g_protoMap;
extern std::unordered_map<int, const std::string> g_flagMap;

#define NETWORKING_FRIEND_CLASS(x) \
class x {\
	friend class Networking;\
	friend std::ostream& operator<<(std::ostream&, const x&);

NETWORKING_FRIEND_CLASS(Info)
public:
	Info() = default;
	Info(const addrinfo *ai);
private:
	int m_family = AF_UNSPEC;
	int m_port = 0;
	int m_sockType = 0;
	int m_flags = 0;
  int m_addrlen = 0;
	std::string m_host;
};

NETWORKING_FRIEND_CLASS(Socket)
public:
	Socket() = default;
	Socket(const addrinfo &ai);
private:
	sockaddr_storage m_sockaddr = {0};
	int m_addrlen = 0;
	SOCKET m_socket = INVALID_SOCKET;
	int m_family = AF_UNSPEC;
	int m_port = 0;
	int m_sockType = 0;
	int m_flags = 0;
	std::string m_host;
public:
	void UpdateName();
	void Bind(const addrinfo&);
};

NETWORKING_FRIEND_CLASS(Server)
public:
	Server(const std::string &host, const std::string &service, int family,
		int sockType, unsigned short backLog, unsigned short millisTimeout);
private:
	Info m_info;
	Socket m_socket;
};

NETWORKING_FRIEND_CLASS(Client)
public:
private:
	Info m_info;
	Socket m_socket;
};

struct Networking {
	Networking() = delete;
	// static const std::string GetSockInfoStr(const addrinfo&);
};

#endif