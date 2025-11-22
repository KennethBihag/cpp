#include "socket.h"

#include <iostream>

using std::cerr; using std::clog;

Socket::Socket()
  : m_sockaddr((sockaddr*)new sockaddr_storage{})
{

}

Socket::Socket(const Socket &other) {
  m_fd = other.m_fd;
  m_config = other.m_config;
  const int len = other.m_config->m_result->ai_addrlen;
  m_sockaddr = (sockaddr*)new char[len];
  memcpy(m_sockaddr, other.m_sockaddr, len);
  m_sockInfo = other.m_sockInfo;
  m_rem = other.m_rem;
  memcpy(recvBuffer, other.recvBuffer, s_rcvBfrSz);
}

Socket::Socket(const Config *config) : Socket()
{
  m_config = config;
	if(!config || !config->m_result){
		cerr << __func__ << ": config is invalid\n";
		exit(EXIT_FAILURE);
	}
	const addrinfo &r = *m_config->m_result;
	m_fd = socket(r.ai_family, r.ai_socktype, r.ai_protocol);
	if(m_fd == INVALID_SOCKET){
		cerr << __func__ << ":socket failed\n";
		exit(EXIT_FAILURE);
	}
}

Socket::~Socket(){
	delete m_sockaddr;
}

void Socket::Activate(ActivateFunc bindOrConnect){
	int error = EXIT_FAILURE;
	if(bindOrConnect != bind && bindOrConnect != connect){
			cerr << __func__ << ": activate function not allowed\n";
			exit(error);
	}

	const auto &ai = *m_config->m_result;
	error = bindOrConnect(m_fd, ai.ai_addr, ai.ai_addrlen);
	if(error){
		cerr << __func__ << ": could not bind/connect\n";
		exit(error);
	}

	UpdateInfo();
}

int Socket::UpdateInfo(){
	memset(m_sockaddr, 0, sizeof(sockaddr_storage));
	int len = m_config->m_result->ai_addrlen;
	int error = getsockname(m_fd, m_sockaddr, &len);
	if(error){
		cerr << __func__ << ": getsockname failed\n";
		exit(error);
	}
	m_sockInfo = EndPoint(m_sockaddr, len);
  return error;
}

Socket* Socket::Accept() const {
  Socket *client = new Socket{};
  Socket &ret = *client;
  int len = m_config->m_result->ai_addrlen;
  ret.m_fd = accept(m_fd, ret.m_sockaddr, &len);
  if(ret.m_fd == INVALID_SOCKET){
    cerr << __func__ << ": accept failed\n";
    delete client;
    client = nullptr;
  }

  return client;
}

  int Socket::Receive(char *buffer, int len) const {
    return recv(m_fd, buffer, len, 0);
  }
  int Socket::Send(const char *message, int len) const {
    return send(m_fd, message, len, 0);
  }