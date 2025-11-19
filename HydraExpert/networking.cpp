#include "networking.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "endpoint.h"

using std::cerr; using std::clog;
using std::string; using std::stringstream;
using std::unordered_map;

const unordered_map<int, string> g_familyMap = {
		{AF_INET, "IPv4"}, {AF_INET6, "IPv6"}, {AF_UNSPEC, "ANY"}
};
const unordered_map<int, string> g_sockMap = {
		{SOCK_DGRAM, "UDP"}, {SOCK_STREAM, "TCP"}, {0, "ANY"}
};
const unordered_map<int, string> g_protoMap = {
		{IPPROTO_UDP, "UDP PROTO"}, {IPPROTO_TCP, "TCP PROTO"}, {0, "ANY"}
};
const unordered_map<int, string> g_flagMap = {
		{4, "ALL"}, {AI_PASSIVE, "PASSIVE"}, {0, "NONE"}, {256, "ALL"}
};

WSAData gWSAData;

namespace Networking {
	void StartUp() {
		int error = (WSAStartup(MAKEWORD(2,2), &gWSAData));
		if(error){
			cerr << "WSAStartup failed!\n";
			exit(error);
		}
	}

	void CleanUp() { WSACleanup(); }

	Config* ConfigServer(const std::string &host, const std::string &port, int family,
							int sockType, unsigned short backLog, int msTimeout)
	{
		addrinfo hints { .ai_flags=AI_PASSIVE, .ai_family=family,
										 .ai_socktype=sockType, .ai_protocol=0 };
		addrinfo *config = nullptr;
		int error = getaddrinfo( host.c_str(), port.empty()?"0":port.c_str(),
														 &hints, &config );
		if(error){
			cerr << __func__ << ": getaddrinfo failed\n";
			exit(error);
		}
		addrinfo *now = config;
		while(now){
			EndPoint ep(now->ai_addr, now->ai_addrlen);
			now = now->ai_next;
		}

		return new Config{hints, config};
	}
};