#include "networking.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

using std::clog;
using std::exception; using std::runtime_error;
using std::string; using std::stringstream;
using std::unordered_map;

unordered_map<int, const string> g_familyMap = {
		{AF_INET, "IPv4"}, {AF_INET6, "IPv6"}, {AF_UNSPEC, "ANY"}
};
unordered_map<int, const string> g_sockMap = {
		{SOCK_DGRAM, "UDP"}, {SOCK_STREAM, "TCP"}, {0, "ANY"}
};
unordered_map<int, const string> g_protoMap = {
		{IPPROTO_UDP, "UDP PROTO"}, {IPPROTO_TCP, "TCP PROTO"}, {0, "ANY"}
};
unordered_map<int, const string> g_flagMap = {
		{AI_ALL, "ALL"}, {AI_PASSIVE, "PASSIVE"}, {0, "NONE"}
};

/* const std::string Networking::GetAllAddrinfoStr(const addrinfo& ai){
	stringstream ssOut;
	const addrinfo *pAi = &ai;
	int i=0;
	while(pAi){
		++i;
		ssOut << i << " " << GetAddrinfoStr(*pAi);
		ssOut << "\n";
		if(pAi == ai.ai_next) break;
		pAi = ai.ai_next;
	}
	return ssOut.str();
} */

/* const std::string Networking::GetSockaddrStr(const addrinfo& ai){

	stringstream ssOut;
	ssOut << "sockaddr @ " << std::hex << ai.ai_addr << std::dec << "{";
	ssOut << "host: " << hostname << "/" << hostname2;
	ssOut << ", service: " << service << "/" << service2;
	ssOut << "}";

	return ssOut.str();
} */