#include "connection.h"
#include "interfaces.h"
#include "usings.h"

#include "logger.hpp"

using namespace HydraExpert;

namespace Knt
{

// IConnection
IConnection::IConnection() : m_pISocket(nullptr), m_pSF(nullptr), m_tvTimeout{0}
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

int Client::Send(const char (&buf)[g_rcvLim], size_t sendLen) const {
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
int Client::Receive(char (&buf)[g_rcvLim]) const {
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
    FD_ZERO(&m_fdsMaster);
}

void Server::Activate() const {
    IConnection::Activate(bind);
    if(m_pISocket->m_sockType == SOCK_STREAM){
        if(listen(m_pISocket->m_sSock, 10))
            ThrowNetworkError("Could not listen!");
    }
    Logger::Log(Logger::Out, "Bound and Listening", GetSockInfoStr());

    FD_SET(m_pISocket->m_sSock, &m_fdsMaster);
    SOCKET maxSocket = m_pISocket->m_sSock;

    while(true){
        fd_set fdsRead = m_fdsMaster;
        fd_set fdsWrite = m_fdsMaster;
        if (select(maxSocket+1, &fdsRead, &fdsWrite, 0, &m_tvTimeout) < 0)
            ThrowNetworkError("select failed");
        for(SOCKET i=1; i<=maxSocket; ++i){
            if(FD_ISSET(i, &fdsRead)){
                if(i == m_pISocket->m_sSock){ // new connection
                    Accept();
                    const SOCKET &clSck = m_vupPeers.back()->m_pISocket->m_sSock;
                    FD_SET(clSck, &m_fdsMaster);
                    maxSocket = std::max(clSck, maxSocket);
                } else { // got message from a client
                    char rcvMsg[g_rcvLim]{};
                    auto itr = GetClById(i);
                    if(Receive(rcvMsg, i) >= 0){
                        char buff[256]{};
                        sprintf(buff, "Received from sock[%d]",(*itr)->m_pISocket->m_sSock);
                        Logger::Log(Logger::Out, buff, rcvMsg);
                    } else {
                        m_vupPeers.erase(itr);
                        FD_CLR(i, &m_fdsMaster);
                    }
                    
                }
                LogClientCount();
                break;
            }
            if(FD_ISSET(i, &fdsWrite)){
                char buff[g_rcvLim]{};
                static const char *reply = "Hello from server non-blocking!";
                sprintf(buff, "%s", reply);
                int sent = Send(buff, strlen(reply), i);
                // close connection after sending
                auto itr = GetClById(i);
                sprintf(buff, "Sent reply to [%d]", (*itr)->m_pISocket->m_sSock);
                Logger::Log(Logger::Inf, buff, "");
                m_vupPeers.erase(itr);
                FD_CLR(i, &m_fdsMaster);
                LogClientCount();
                break;
            }
        }
    }
}

void Server::Accept() const{
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

int Server::Send(const char (&msg)[g_rcvLim], size_t sendLen) const {
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

int Server::Send(const char (&msg)[g_rcvLim], size_t sendLen, SOCKET s) const {
    auto clIt = GetClById(s);
    Client &cl = **clIt;

    int sent = -1;
    if(m_pISocket->m_sockType != SOCK_DGRAM){
        sent = cl.Send(msg, sendLen);
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

int Server::Receive(char (&msg)[g_rcvLim]) const {
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

int Server::Receive(char (&msg)[g_rcvLim], SOCKET s) const {
    Client &cl = **GetClById(s);
    if(m_pISocket->m_sockType != SOCK_DGRAM)
        return cl.Receive(msg);
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

std::vector<std::unique_ptr<Client>>::iterator Server::GetClById(SOCKET s) const {
    for(auto i=m_vupPeers.begin(); i<m_vupPeers.end(); ++i)
        if(s == (*i)->m_pISocket->m_sSock) return i;
    return m_vupPeers.end();
}

void Server::LogClientCount() const {
    char buff[128];
    sprintf(buff, "%d clients", m_vupPeers.size());
    Logger::Log(Logger::Inf, __FUNCTION__, buff);
}

} // namespace Knt
