#ifndef CONNECTION_H
#define CONNECTION_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "socket_factory.h"

using namespace HydraExpert;

namespace Knt {


class IConnection {
protected:
    std::unique_ptr<CSocket> m_pISocket;
    std::unique_ptr<SocketFactory> m_pSF;
    TIMEVAL m_tvTimeout;

    void Close();
public:
    IConnection();
    IConnection(const std::string&, const std::string&, int, int, int);
    virtual ~IConnection();
    virtual int Send(const char (&)[g_rcvLim], size_t) const = 0;
    virtual int Receive(char (&)[g_rcvLim]) const = 0;
    const std::string GetSockInfoStr() const;
    const std::string GetAddrInfoStr() const;
    void Activate(decltype(bind)) const;
    virtual void Activate() const = 0;
};

class Client: public IConnection{
    friend class Server;
    std::unique_ptr<CSocket> m_upPeer;
public:
    Client(const std::string&, const std::string&, int = AF_UNSPEC,
      int = 0);
    Client(CSocket*);
    void Activate() const override;
    int Send(const char (&)[g_rcvLim], size_t) const override final;
    int Receive(char (&)[g_rcvLim]) const override final;
    ~Client();
};

class Server: public IConnection{
    mutable std::vector<std::unique_ptr<Client>> m_vupPeers;
    fd_set m_fdsMaster;
public:
    Server(const std::string& = "", const std::string& = "",
      int = AF_UNSPEC, int = 0);
    void Activate() const override;
    void Accept() const;
    int Send(const char (&)[g_rcvLim], size_t) const override final;
    int Receive(char (&)[g_rcvLim]) const override final;
private:
    void LogClientCount() const;
    std::vector<std::unique_ptr<Client>>::iterator GetClById(SOCKET) const;
    int Send(const char (&)[g_rcvLim], size_t, SOCKET) const;
    int Receive(char (&)[g_rcvLim], SOCKET) const;
};

}

#endif