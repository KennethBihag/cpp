#include "socket.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "interfaces.h"
#include "usings.h"

using namespace Knt;

CSocket::CSocket() : m_sockAddr{0}, m_sALen{0},
    m_sSock{INVALID_SOCKET}, m_state{State::INVALID}, m_sockType{0}
{
    ;
}

CSocket::CSocket(const addrinfo& aI) : CSocket() {
    m_sSock = socket(aI.ai_family, aI.ai_socktype, aI.ai_protocol);
    m_sALen = aI.ai_addrlen;  
    memcpy(&m_sockAddr, aI.ai_addr, m_sALen);
    UpdateState();
}

CSocket::CSocket(SOCKET p_sock) : CSocket() {
    m_sSock = p_sock;
    UpdateState();
}

CSocket::CSocket(SOCKET p_sock, sockaddr *p_pSockAddr, int p_addLen,
  int p_sockType, State p_state) : m_sockAddr{0}, m_sALen{p_addLen},
  m_sSock{p_sock}, m_state{p_state}, m_sockType{p_sockType}
{
    memcpy(&m_sockAddr, p_pSockAddr, m_sALen);
}

CSocket::~CSocket()
{
    stringstream ss("ISocket::Dtor @");
    ss << std::hex << this << std::dec;
    ss << "[" << m_sSock << "]";
    switch (m_state)
    {
    case State::ON:
        if(closesocket(m_sSock)){
            ss << " ! Could not close Socket !";
            ThrowNetworkError(ss.str());
        } else {
            ss << " : Closed";
        }
        break;
    default:
        break;
    }
    clog << ss.str() << "\n";
}

CSocket::State CSocket::UpdateState(){
    int optVal, optLen=sizeof(int);
    if(getsockopt(m_sSock, SOL_SOCKET, SO_TYPE, (char*)&optVal, &optLen))
        m_state = State::INVALID;
    else
        m_state = State::OFF;
    m_sockType = optVal;
    if(!getsockname(m_sSock, (sockaddr*)&m_sockAddr, &m_sALen))
        m_state = State::ON;
    
    return m_state;
}

const string CSocket::InfoStr() const {
    stringstream infStr;
    infStr << "CSocket@";
    infStr << std::hex << this << std::dec << "[";
    infStr << m_sSock << "]";
    infStr << ":" << g_sockMap[m_sockType];
    infStr << ":" << (m_state==State::INVALID?"INVALID" : m_state==State::OFF?"OFF" : "ON") << " {";
    const sockaddr *sockAddr =
        reinterpret_cast<const sockaddr*>(&m_sockAddr);
    infStr << Interfaces::GetSockInfo(sockAddr, m_sALen);
    infStr << "}";

    return infStr.str();
}
