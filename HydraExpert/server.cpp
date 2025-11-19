#include "server.h"

#include <iostream>

#include "http.h"

using std::cerr; using std::clog;

Server::Server(const Socket &socket, int backLog)
  : m_socket(new Socket(socket)), m_backLog(backLog)
{
  if(socket.m_fd == INVALID_SOCKET || !socket.m_sockaddr){
    cerr << __func__ << ": invalid socket\n";
    exit(EXIT_FAILURE);
  }
  FD_ZERO(&m_master);
}

Server::~Server(){
  delete m_socket;
}

void Server::Start(){
  int error = listen(m_socket->m_fd, m_backLog);
  if(error){
    cerr << __func__ << ": listen failed\n";
    exit(error);
  }
  clog << "Listening to " << m_socket->m_sockInfo.m_host << ":"
       << m_socket->m_sockInfo.m_service << "\n";
}

void Server::Process() {
  while(true){
    Socket *client = m_socket->Accept();
    clog << "Accepted socket " << client->m_fd << "\n";
    m_clientMap[client->m_fd] = client;
    char message[2048]{};
    client->Receive(message, sizeof(message));
    clog << "Received from " << client->m_fd << "\n" << message << "\n";
    client->Send(HTTP::m_Template, strlen(HTTP::m_Template));
    clog << "Sent to " << client->m_fd << "\n";
    closesocket(client->m_fd);
    clog << "Closed " << client->m_fd << "\n";
    m_clientMap.erase(client->m_fd);
    delete client;
    clog << "Deleted client " << client->m_fd << "\n";
  }
}
