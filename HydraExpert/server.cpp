#include "server.h"

#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <vector>

#include "http.h"

using std::cerr; using std::clog; using std::endl;
using std::mutex;
using std::string; using std::stringstream;
using std::thread;
using std::vector;
using namespace HTTP;

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

int Server::CloseSocket(const Socket &s){
  int ret = closesocket(s.m_fd);
  m_clientMap.erase(s.m_fd);
  if(ret)
    cerr << __FUNCTION__ << ":closesocket failed code " << ret << endl;
  return ret;
}

int HandleGet(Server *svr, Socket *sock, Request *req){
  string ret;
  if(req->m_path == "/")
    ret = GetIndexDoc();
  else
    ret = GetDoc(req->m_path);
  return sock->Send(ret.c_str(), ret.length());
}

int HandleRequest(Server *svr, Socket *client){
    gMutex.lock();
    svr->m_clientMap[client->m_fd] = client;
    gMutex.unlock();
    char fdStr[6]; snprintf(fdStr, 6, "[%d]", client->m_fd);
    stringstream message;

    while(true){
      char chunk[256]{};
      int got = client->Receive(chunk, sizeof(chunk));
      if(got < 1){
        gMutex.lock();
        svr->CloseSocket(*client);
        gMutex.unlock();
        clog << fdStr << " closed\n";
        delete client;
        break;
      } else if((size_t)got < sizeof(chunk)) {
        message << chunk;
        break;
      } else {
        message << chunk;
        if(strstr(chunk, HTTP::s_end))
          break;
      }
    }

    HTTP::Request req(message.str().c_str(), message.str().length());
    switch(req.m_method){
    case HTTP::GET:
      {
        int sent = HandleGet(svr, client, &req);
        clog << fdStr << " " << sent << "B sent\n";
        if(sent < 0){
          cerr << fdStr << "Error handling GET, code " << sent << endl;
        }
        break;
      }
    default:
      {
        auto found = "";
        for(const auto &e : g_MethodMap){
          if(e.second == req.m_method)
            found = e.first.c_str();
        }
        clog << fdStr << " " << found << " not supported";
        break;
      }
    }

    svr->CloseSocket(*client);
    delete client;
    clog << fdStr << " closed\n";
    return EXIT_SUCCESS;
}

void Server::Process() {
  // vector<thread> threads;
  while(true){
    Socket *client = m_socket->Accept();
    if(client){
      clog << "[" << client->m_fd << "] Connected\n";
      thread(HandleRequest, this, client).detach();
    }
  }
}
