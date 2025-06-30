#include "interfaces.h"

#include <sstream>

#include "usings.h"

#ifdef _WIN32
static std::allocator<IP_ADAPTER_ADDRESSES_LH> g_adapters;
#else
static ifaddrs *g_addresses;
#endif

static unsigned long g_aSz = 20'000;
static const unsigned int g_buffSz = 128;

const string Knt::Interfaces::GetAddrInfo(const addrinfo *pAI){
    stringstream ssOut;

    ssOut << "addrinfo" << "@" << std::hex << pAI << std::dec;
    ssOut << ":" << g_familyMap[pAI->ai_family]
            << ":" << g_sockMap[pAI->ai_socktype]
            << ":" << g_sockMap[pAI->ai_protocol]
            << ":" << g_flagMap[pAI->ai_flags];

    return ssOut.str();
}

const string Knt::Interfaces::GetInterfaces(){
    stringstream adptrsBffr;
    PIP_ADAPTER_ADDRESSES adapters = nullptr;
#ifdef _WIN32
    do {
        adapters = g_adapters.allocate(g_aSz);
        if (!adapters)
            ThrowError("allocate",GETSYSERROR());
        if( GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters,
                                &g_aSz) )
            ThrowNetworkError("GetAdapterAddresses");
        else
            break;
    } while(!adapters);

    PIP_ADAPTER_ADDRESSES adapter = adapters;
    while(adapter){
        char name[128];
        sprintf_s(name, "Name:%S\n", adapter->FriendlyName);
        adptrsBffr << name;
        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
        while(address){
            adptrsBffr << "\t" << GetSockInfo(address->Address.lpSockaddr,
              address->Address.iSockaddrLength) << "\n";
            address = address->Next;
        }
        adapter = adapter->Next;
    }

    g_adapters.deallocate(adapters, g_aSz);
#else
    if(getifaddrs(&g_addresses) == -1)
        ThrowError("getifaddrs",GETSYSERROR);
    ifaddrs *adapter = g_addresses;
    while(adapter){
        adptrsBffr << GetSockInfo(*adapter);
        adapter = adapter->ifa_next;
    }
#endif
    return adptrsBffr.str();
}

string Knt::Interfaces::GetSockInfo(const sockaddr *sockAddr, int len){
    stringstream ssTmp;
    char buff1[g_buffSz], buff2[g_buffSz];

    ssTmp << "sockaddr@" << std::hex << sockAddr << std::dec;
    ssTmp << ":" << g_familyMap[sockAddr->sa_family];
    ssTmp << " { ";
    getnameinfo(sockAddr, len, buff1, g_buffSz,
                buff2, g_buffSz, NI_NUMERICHOST|NI_NUMERICSERV);
    ssTmp << buff1 << ":" << buff2 << " - ";
    getnameinfo(sockAddr, len, buff1, g_buffSz,
                buff2, g_buffSz, 0);
    ssTmp << buff1 << ":" << buff2 << " }";

    return ssTmp.str();
}