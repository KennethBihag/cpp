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
public:
    std::unique_ptr<CSocket> m_pISocket;
    std::unique_ptr<SocketFactory> m_pSF;

    void Close();
public:
    IConnection();
    IConnection(const std::string&, const std::string&, int, int, int);
    virtual ~IConnection();
    virtual int Send(const char (&)[g_rcvLim], size_t) = 0;
    virtual int Receive(char (&)[g_rcvLim]) = 0;
    const std::string GetSockInfoStr() const;
    const std::string GetAddrInfoStr() const;
    void Activate(decltype(bind)) const;
    virtual void Activate() const = 0;
};

class Client: public IConnection{
    std::unique_ptr<CSocket> m_upPeer;
public:
    Client(const std::string&, const std::string&, int = AF_UNSPEC,
      int = 0);
    Client(CSocket*);
    void Activate() const override;
    int Send(const char (&)[g_rcvLim], size_t) override final;
    int Receive(char (&)[g_rcvLim]) override final;
    ~Client();
};

class Server: public IConnection{
    std::vector<std::unique_ptr<Client>> m_vupPeers;
public:
    Server(const std::string& = "", const std::string& = "",
      int = AF_UNSPEC, int = 0);
    void Activate() const override;
    void Accept();
    int Send(const char (&)[g_rcvLim], size_t) override final;
    int Receive(char (&)[g_rcvLim]) override final;
};

}

#endif