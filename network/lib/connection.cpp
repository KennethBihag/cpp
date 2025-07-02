#include "connection.h"
#include "interfaces.h"
#include "usings.h"

#include "logger.hpp"

using namespace HydraExpert;

namespace Knt
{

// IConnection
IConnection::IConnection() : m_pISocket(nullptr), m_pSF(nullptr)
{
    ;
}

IConnection::IConnection(const string& host, const string& port,
  int family, int sockType, int flags) : IConnection() {
    m_pSF.reset(new SocketFactory);
    CSocket *socket = m_pSF->CreateSocket(host, port, family, sockType, flags);
    m_pISocket.reset(socket);
}

IConnection::~IConnection()
{
    ;
}

const string IConnection::GetAddrInfoStr() const {
    return m_pSF->GetAddressesStr();
}

const string IConnection::GetSockInfoStr() const {
    return m_pISocket->InfoStr();
}

void IConnection::Close(){
    m_pISocket.reset(nullptr);
}

void IConnection::Activate(decltype(bind) func) const {
    string funcName = func == bind ? "bind" : "connect";
    string errFunc = "Could not " + funcName;

    sockaddr_storage &sas = m_pISocket->m_sockAddr;
    sockaddr *pAddr = (sockaddr*)&sas;
    int &len = m_pISocket->m_sALen;

    bool bInvoke = false;

    if(m_pISocket->m_sockType == SOCK_STREAM)
        bInvoke = true;
    else {
        if(funcName == "bind")
            bInvoke = true;
        else
            m_pISocket->m_state = CSocket::State::ON;
    }

    if(bInvoke){
        if(func(m_pISocket->m_sSock, pAddr, len))
            ThrowNetworkError(errFunc);
        m_pISocket->UpdateState();
    }
}

// Client
Client::Client(const string& host, const string& port,
  int family, int sockType) : IConnection(host, port, family, sockType,
  AI_ALL){
    m_upPeer = std::unique_ptr<CSocket>(nullptr);
}

Client::Client(CSocket *pCSocket){
    m_pISocket.reset(pCSocket);
}

Client::~Client(){
}

void Client::Activate() const {
    IConnection::Activate(connect);
}

int Client::Send(const char (&buf)[g_rcvLim], size_t sendLen) {
    if(m_pISocket->m_state != CSocket::State::ON)
        return -1;
    std::cout << "Try sending...\n";
    if(m_pISocket->m_sockType == SOCK_STREAM){
        return send(m_pISocket->m_sSock, buf, sendLen, 0);
    } else {
        sockaddr_storage &sas = m_pISocket->m_sockAddr;
        sockaddr *pAddr = (sockaddr*)&sas;
        int &len = m_pISocket->m_sALen;

        int sent = sendto(m_pISocket->m_sSock, buf, sendLen, 0, pAddr, len);
        Logger::Log(Logger::Inf, "Sendto", Interfaces::GetSockInfo(pAddr, len));
        return sent;
    }
}
int Client::Receive(char (&buf)[g_rcvLim]) {
    if(m_pISocket->m_state != CSocket::State::ON)
        return -1;
    std::cout << "Try receiving...\n";
    if(m_pISocket->m_sockType == SOCK_STREAM){
        return recv(m_pISocket->m_sSock, buf, g_rcvLim-1, 0);
    } else {
        sockaddr_storage &sas = m_pISocket->m_sockAddr;
        sockaddr *pAddr = (sockaddr*)&sas;
        int &len = m_pISocket->m_sALen;

        int received = recvfrom(m_pISocket->m_sSock, buf, g_rcvLim-1, 0, pAddr, &len);
        Logger::Log(Logger::Inf, "Recvfrom", Interfaces::GetSockInfo(pAddr, len));
        return received;
    }
    
}

// Server
Server::Server(const string& host, const string& port,
  int family, int sockType) : IConnection(host, port, family, sockType,
  AI_PASSIVE)
{
    ;
}

void Server::Activate() const {
    IConnection::Activate(bind);
    if(m_pISocket->m_sockType == SOCK_STREAM){
        if(listen(m_pISocket->m_sSock, 10))
            ThrowNetworkError("Could not listen!");
    }
}

void Server::Accept(){
    if(m_pISocket->m_sockType != SOCK_DGRAM){
        int len = m_pISocket->m_sALen;
        sockaddr_storage storage{};

        SOCKET clSock = accept(m_pISocket->m_sSock, (sockaddr*)&storage, &len);

        if(!ISVLDSCKT(clSock))
            ThrowNetworkError("Could not accept connection!");
        CSocket *clSocket = new CSocket(clSock, (sockaddr*)&storage, len,
            m_pISocket->m_sockType, CSocket::State::ON);

        Logger::Log(Logger::Inf, "Client sock info", clSocket->InfoStr());
        m_vupPeers.emplace_back(make_unique<Client>(clSocket));
    }
}

int Server::Send(const char (&msg)[g_rcvLim], size_t sendLen) {
    int sent = -1;
    if(m_pISocket->m_sockType != SOCK_DGRAM){
        sent = m_vupPeers.back()->Send(msg, sendLen);
        m_vupPeers.pop_back();
    } else {
/*         sockaddr_storage storage{};
        int len = m_pISocket->m_sALen;
        sent = sendto(m_pISocket->m_sSock, msg, sendLen, 0, (sockaddr*)&storage, len); */

        auto &clientPeer = *m_vupPeers.back();
        sockaddr *pAddr = (sockaddr*)&(clientPeer.m_pISocket->m_sockAddr);
        int len = clientPeer.m_pISocket->m_sALen;
        sent = sendto(m_pISocket->m_sSock, msg, sendLen, 0, pAddr, len);
        if(sent < 0)
            ThrowNetworkError("sendto failed");
        clientPeer.m_pISocket->UpdateState();
        m_vupPeers.pop_back();

    }
    return sent;
}
int Server::Receive(char (&msg)[g_rcvLim]) {
    if(m_pISocket->m_sockType != SOCK_DGRAM)
        return m_vupPeers.back()->Receive(msg);
    else{
        sockaddr_storage storage{};
        int len = m_pISocket->m_sALen;
        int received = recvfrom(m_pISocket->m_sSock, msg, g_rcvLim-1, 0,
          (sockaddr*)&storage, &len);
        CSocket *pClientSock = new CSocket(0, (sockaddr*)&storage, len, m_pISocket->m_sockType, CSocket::State::ON);
        m_vupPeers.emplace_back(make_unique<Client>(pClientSock));
        string peerInfo = Interfaces::GetSockInfo((sockaddr*)&storage, len);
        Logger::Log(Logger::Inf, "Received from info", peerInfo);

        return received;
    }

}

} // namespace Knt
