#ifndef SERVER_H
#define SERVER_H

#include <map>

#include "http.h"
#include "socket.h"

struct Server {
private:
  Socket *m_socket = nullptr;
  int m_backLog = 0;
  fd_set m_master;
  std::map<SOCKET, Socket*> m_clientMap;
  int CloseSocket(const Socket&);
public:
  Server(const Socket& socket, int backLog);
  ~Server();
  void Start();
  void Process();

  friend int HandleRequest(Server*, Socket*);
  friend int HandleGet(Server*, Socket*, HTTP::Request*);
};

#endif