#include "networking.h"

#include <iostream>

using std::clog;
using std::runtime_error;
using std::string;

Server::Server(const string &host, const string &service, int family, int sockType,
  unsigned short backLog, unsigned short millisTimeout)
{
	const char *svc = nullptr;
	if(service.empty()) svc = "0";
  else svc = service.c_str();
	addrinfo hints {
    .ai_flags = AI_PASSIVE, .ai_family = family, .ai_socktype = sockType
  };
  clog << "Hints: " << Info(&hints) << "\n";
  addrinfo *serverAi = nullptr;
  if(getaddrinfo(host.c_str(), svc, &hints, &serverAi))
    throw runtime_error("getaddrinfo");
  m_info = Info(serverAi);
  clog << "Configured: " << m_info << "\n";
  m_socket = Socket(*serverAi);
  clog << "Created socket: " << m_socket << "\n";
  m_socket.Bind(*serverAi);
  clog << "Bound: " << m_socket << "\n";
  freeaddrinfo(serverAi);
}
