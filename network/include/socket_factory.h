#ifndef SOCKET_FACTORY_H
#define SOCKET_FACTORY_H

#include <memory>
#include <string>

#include "socket.h"

namespace HydraExpert {
    void MyFree(LPADDRINFO);
    using namespace Knt;
    class SocketFactory {
        std::unique_ptr<addrinfo, decltype(&MyFree)> m_paiResult;

    public:

        SocketFactory();
        ~SocketFactory();
        CSocket *CreateSocket(
            const std::string& = "", const std::string& = "",
            int = AF_UNSPEC, int = 0, int = 0
          );

        const std::string GetAddressesStr() const;

    };
}

#endif