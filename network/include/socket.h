#ifndef SOCKET_H
#define SOCKET_H

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>

#include "networking.h"

namespace Knt {
    class CSocket {
    public:
        friend class IConnection;
        friend class Client;
        friend class Server;

        enum State: unsigned char{
            INVALID, OFF, ON
        };

    protected:
        sockaddr_storage m_sockAddr;
        int m_sALen;
        SOCKET m_sSock;
        State m_state;
        int m_sockType;

        State UpdateState();

    public:
        CSocket();
        CSocket(const addrinfo&);
        CSocket(SOCKET);
        CSocket(SOCKET, sockaddr*, int, int, State);
        ~CSocket();
        const std::string InfoStr() const;
    }; // class ISocket

} // namespace Knt

#endif