#ifndef SOCKET_H
#define SOCKET_H

#include "common.h"
#include "config.h"
#include "endpoint.h"

using ActivateFunc = decltype(bind);

struct Socket {
  static const unsigned char s_rcvBfrSz = 64;
  SOCKET m_fd = INVALID_SOCKET;
  const Config *m_config = nullptr;
  sockaddr *m_sockaddr = nullptr;
  EndPoint m_sockInfo{};
  unsigned char m_rem = s_rcvBfrSz;
  char recvBuffer[s_rcvBfrSz]{};
  Socket();
  Socket(const Config*);
  ~Socket();
  Socket(const Socket &other);
  void Activate(ActivateFunc bindOrConnect);
  Socket* Accept() const;
  int Receive(char*, int) const;
  int Send(const char*, int) const;
private:
  int UpdateInfo();
};

#endif