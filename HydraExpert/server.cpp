#include "server.h"

#include <iomanip>
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
    clog << "Accepted [" << client->m_fd << "]\n";
    gMutex.lock();
    svr->m_clientMap[client->m_fd] = client;
    gMutex.unlock();
    int sent = 0;
    char fdStr[6];
    snprintf(fdStr, 6, "[%d]", client->m_fd);
GET_MESSAGE:
    char message[256]{};
    int got = client->Receive(message, sizeof(message));
    clog << fdStr << " sent " << got << "\n";
    if(got < 1){
      closesocket(client->m_fd);
      clog << fdStr << " closed\n";
      gMutex.lock();
      svr->m_clientMap.erase(client->m_fd);
      gMutex.unlock();
      clog << fdStr << " deleted\n";
      delete client;
      goto END;
    }
    clog << fdStr << " " << message << "\n";
    sent = client->Send(HTTP::m_Template, strlen(HTTP::m_Template));
    clog << fdStr << " got " << sent << "\n";
    goto GET_MESSAGE;
END:
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
