#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <ctime>

#include "includes.hpp"

using namespace std;

void br()
{
    cout << "---\n";
}

int main(const int argc, const char *argv[])
{
    time_t tmnow;
    time(&tmnow);
    const char *timeNow = ctime(&tmnow);
    cout << "Time now: " << timeNow << '\n';
    br();
#ifdef _WIN32
// init WSA
    WSADATA d;
    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        cerr << "Error!\n";
    }
    else
    {
        clog << "No error! :)\n";
        cout << "INFO:\n";
        cout << "\t" << d.iMaxSockets << '\n';
        cout << "\t" << d.iMaxUdpDg << '\n';
        // cout << "\t" << d.lpVendorInfo << '\n';
        cout << "\t" << d.szDescription << '\n';
        cout << "\t" << d.szSystemStatus << '\n';
        cout << "\t" << d.wHighVersion << '\n';
        cout << "\t" << d.wVersion << '\n';
    }

// get adapters
    DWORD asize = 20000;
    PIP_ADAPTER_ADDRESSES adapters;
    do
    {
        adapters = (PIP_ADAPTER_ADDRESSES)malloc(asize);
        if (!adapters)
        {
            printf("Couldn't allocate %ld bytes for adapters.\n", asize);
            WSACleanup();
            return EXIT_FAILURE;
        }
        int r = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, adapters, &asize);
        if (r == ERROR_BUFFER_OVERFLOW)
        {
            printf("GetAdaptersAddresses wants %ld bytes.\n", asize);
            free(adapters);
        }
        else if (r == ERROR_SUCCESS)
        {
            break;
        }
        else
        {
            printf("Error from GetAdaptersAddresses: %d\n", r);
            CleanUp(adapters);
            return EXIT_FAILURE;
        }
    } while (!adapters);
// print adapters
    PIP_ADAPTER_ADDRESSES adapter = adapters;
    while (adapter)
    {
        printf("\nAdapter name: %S\n", adapter->FriendlyName);
        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
        while (address)
        {
            printf("\t%s",
                   address->Address.lpSockaddr->sa_family == AF_INET ? "IPv4" : "IPv6");
            char ap[100];
            char bp[100];
            getnameinfo(address->Address.lpSockaddr, address->Address.iSockaddrLength,
                        ap, sizeof ap, bp, sizeof bp, NI_NUMERICHOST);
            printf("\t%s\t%s\n", ap, bp);
            address = address->Next;
        }
        adapter = adapter->Next;
    }
#else
    ifaddrs *addresses;
    if(getifaddrs(&addresses) == -1){
        cout << "getifaddrs failed\n";
        return EXIT_FAILURE;
    }
    ifaddrs *address = addresses;
    while(address){
        int fam = address->ifa_addr->sa_family;
        if(fam == AF_INET || fam == AF_INET6){
            cout << address->ifa_name << '\t';
            cout << (fam == AF_INET ? "IPv4":"IPv6");
            cout << '\t';
            char ap[128], bp[128];
            const int famsz = fam == AF_INET ?
                sizeof(sockaddr_in) : sizeof(sockaddr_in6);
            getnameinfo(address->ifa_addr, famsz, ap, sizeof ap, bp, sizeof bp,
                        NI_NUMERICHOST);
            cout <<'\t' << ap << '\t' << bp << '\n';
        }
        address = address->ifa_next;
    }
#endif
    br();
    // config local address
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    addrinfo *bindAddr;
    getaddrinfo(0, "8080", &hints, &bindAddr);

    // create socket
    SOCKET srvskt = socket(bindAddr->ai_family, bindAddr->ai_socktype, bindAddr->ai_protocol);
    if(!ISVLDSCKT(srvskt)){
        cerr << "socket() failed(" << GETSCKERR() << ")\n";
#ifdef _WIN32
        CleanUp(adapters);
#endif
        return EXIT_FAILURE; 
    }

    // dual-stack sockets
    int opt{};
    int &&x = setsockopt(srvskt, IPPROTO_IPV6, IPV6_V6ONLY, (char*)&opt, sizeof opt);
    if(x){
        cerr << "setsockopt() failed(" << GETSCKERR() << '\n';
        return EXIT_FAILURE;
    }
    //bind
    if( bind(srvskt, bindAddr->ai_addr, bindAddr->ai_addrlen) ){
        cerr << "bind() failed(" << GETSCKERR() << '\n';
#ifdef _WIN32
        CleanUp(adapters);
#endif
        return EXIT_FAILURE;
    }
    other::PrintIP(bindAddr);
    freeaddrinfo(bindAddr);

// listen
    if(listen(srvskt, 2) < 0){
        cerr << "listen() failed(" << GETSCKERR() << '\n';
        return EXIT_FAILURE;
    }

// accept
    cout << "Waiting...\n";
    sockaddr_storage clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    SOCKET clskt = accept(srvskt, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
    if(!ISVLDSCKT(clskt)){
        cerr << "accept() failed(" << GETSCKERR() << '\n';
        return EXIT_FAILURE;
    }
    addrinfo clInfo{};
    clInfo.ai_addr = reinterpret_cast<sockaddr*>(&clientAddr);
    clInfo.ai_addrlen = clientAddrLen;
    other::PrintIP(&clInfo);
// read request
    char req[1024]; req[1023]='\0';
    recv(clskt, req, 1023, 0);
    cout << "Got request";
    br();
    cout << req;
    br();

// send response
    string responseTime = other::ResponseOk() + "Local time is:" + timeNow;
    int sentBytes = send(clskt, responseTime.c_str(), responseTime.length(), 0);
    cout << "Sent " << sentBytes << " bytes.\n";
    CLOSESKT(clskt);

    CLOSESKT(srvskt);
#ifdef _WIN32
    CleanUp(adapters);
#endif
}
