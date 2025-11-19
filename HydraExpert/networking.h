#ifndef NETWORKING_H
#define NETWORKING_H

#include <string>
#include <ostream>
#include <unordered_map>

#include "common.h"
#include "config.h"

extern const std::unordered_map<int, std::string> g_familyMap;
extern const std::unordered_map<int, std::string> g_sockMap;
extern const std::unordered_map<int, std::string> g_protoMap;
extern const std::unordered_map<int, std::string> g_flagMap;

const unsigned short gRecvSz = 64;

namespace Networking {
	void StartUp();
	void CleanUp();
	Config* ConfigServer(const std::string &host, const std::string &port,
			int family, int sockType, unsigned short backLog, int msTimeout);
}

#endif