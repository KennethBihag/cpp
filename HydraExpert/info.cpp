#include "networking.h"

#include <iostream>
#include <stdexcept>

using std::clog;
using std::runtime_error;

Info::Info(const addrinfo *ai)
{
	char hostname[64]{}, service[64]{};
	if(ai->ai_addr && getnameinfo(ai->ai_addr, ai->ai_addrlen, hostname, 64,
    service, 64, NI_NUMERICHOST|NI_NUMERICSERV))
		  throw runtime_error("getnameinfo");
  m_family = ai->ai_family;
  m_flags = ai->ai_flags;
  m_host = hostname;
  m_port = atoi(service);
  m_sockType = ai->ai_socktype;
  m_addrlen = ai->ai_addrlen;
}

std::ostream &operator<<(std::ostream &os, const Info &info){
  char buffer[256]{};
  auto tae = g_familyMap[1];
  sprintf_s(buffer, "{host: \"%s\", port: %d, family: \"%s\", socket-type: \"%s\""
    "flags: \"%s\", length:%d}",
    info.m_host.c_str(), info.m_port, g_familyMap[info.m_family].c_str(),
    g_sockMap[info.m_sockType].c_str(), g_flagMap[info.m_flags].c_str(),
    info.m_addrlen);
  return os << buffer;
}