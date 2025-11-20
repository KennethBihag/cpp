#include "server.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "http.h"

using std::cerr; using std::clog;
using std::mutex;
using std::thread;
using std::vector;

mutex gMutex;


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

int HandleGet(Server *svr, Socket *ptr){
    Socket *client = (Socket*)ptr;
    clog << "Accepted socket " << client->m_fd << "\n";
    gMutex.lock();
    svr->m_clientMap[client->m_fd] = client;
    gMutex.unlock();
    char message[2048]{};
    client->Receive(message, sizeof(message));
    clog << "Received from " << client->m_fd << "\n" << message << "\n";
    client->Send(HTTP::m_Template, strlen(HTTP::m_Template));
    clog << "Sent to " << client->m_fd << "\n";
    closesocket(client->m_fd);
    clog << "Closed " << client->m_fd << "\n";
    gMutex.lock();
    svr->m_clientMap.erase(client->m_fd);
    gMutex.unlock();
    delete client;
    clog << "Deleted client " << client->m_fd << "\n";

    return EXIT_SUCCESS;
}

void Server::Process() {
  // vector<thread> threads;
  while(true){
    Socket *client = m_socket->Accept();
    // threads.emplace_back(HandleGet, client);
    thread(HandleGet, this, client).detach();
  }
}
