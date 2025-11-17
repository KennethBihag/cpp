#include "networking.h"

#include <iostream>

using std::runtime_error;
using std::ostream;
using std::clog;

ostream &operator<<(ostream &os, const Socket &socket){
  char buffer[256]{};
  sprintf_s(buffer,"{host:%s, port:%d, family:%s, len:%d}",
    socket.m_host.c_str(), socket.m_port, g_familyMap[socket.m_family].c_str(),
    socket.m_addrlen);
  return os << buffer;
}

void Socket::UpdateName(){
  sockaddr *pSA = (sockaddr*)&m_sockaddr;
  if(getsockname(m_socket, pSA, &m_addrlen))
    throw runtime_error("getsockname");
  char host[64]{}, port[64]{};
  m_family = pSA->sa_family;
  if(getnameinfo(pSA, m_addrlen, host, 64, port, 64,
    NI_NUMERICHOST|NI_NUMERICSERV))
      throw runtime_error("getnameinfo");
  m_host = host; m_port = atoi(port);
}

Socket::Socket(const addrinfo &ai){
  m_flags = ai.ai_flags;
  m_socket = socket(ai.ai_family, ai.ai_socktype, ai.ai_protocol);
  m_addrlen = ai.ai_addrlen;
  if(m_socket == INVALID_SOCKET) throw runtime_error("socket");
}

void Socket::Bind(const addrinfo &ai){
  if(bind(m_socket, ai.ai_addr, ai.ai_addrlen))
    throw runtime_error("bind");
  UpdateName();
}