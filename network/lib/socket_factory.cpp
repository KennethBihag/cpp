#include "socket_factory.h"

#include <iomanip>
#include <sstream>

#include "interfaces.h"

#include "colored_console.hpp"

#include "usings.h"


using namespace Knt;

namespace HydraExpert {

void MyFree(LPADDRINFO lpa){
    clog << "Destroyed addrinfo@" << std::hex << lpa << std::dec << ")\n";
    freeaddrinfo(lpa);
}

SocketFactory::SocketFactory() : m_paiResult(nullptr, MyFree)
{
    ;
}

SocketFactory::~SocketFactory()
{
    ;
}

CSocket *SocketFactory::CreateSocket(const string &host,
  const string &port, int family, int sockType, int flags){
    addrinfo hints {
        .ai_flags = flags,
        .ai_family = family,
        .ai_socktype = sockType
    };

    clog << "Hints: " << Interfaces::GetAddrInfo(&hints) << std::endl;
    addrinfo *pAI;

    const char *_host = host.c_str();
    const char *_port = port.empty() ? "0" : port.c_str();

    if(getaddrinfo(_host, _port, &hints, &pAI))
        ThrowNetworkError("CreateSocket:getaddrinfo failed");

    m_paiResult.reset(pAI);
    
    return new CSocket(*pAI);
}

const string SocketFactory::GetAddressesStr() const {
    stringstream ssOut("");
    const addrinfo *currAi = m_paiResult.get();
    int iAddrCnt = 0;

    ssOut << "SocketFactory@" << std::hex << this << std::dec;
    ssOut << "\n";

    while(currAi){
        ssOut << "\t" << ++iAddrCnt << Interfaces::GetAddrInfo(currAi) << "\n";
        ssOut << "\t\t" << Interfaces::GetSockInfo(
            currAi->ai_addr, currAi->ai_addrlen) << "\n";
        currAi = currAi->ai_next;
    }

    return ssOut.str();

}

}