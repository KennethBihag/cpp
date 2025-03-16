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
            return -1;
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
            free(adapters);
            WSACleanup();
            return -1;
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
            getnameinfo(address->Address.lpSockaddr, address->Address.iSockaddrLength, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            printf("\t%s\n", ap);
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
            char ap[128];
            const int famsz = fam == AF_INET ?
                sizeof(sockaddr_in) : sizeof(sockaddr_in6);
            getnameinfo(address->ifa_addr, famsz, ap, sizeof ap, 0, 0, NI_NUMERICHOST);
            cout <<'\t' << ap << '\n';
        }
        address = address->ifa_next;
    }
#endif

// config local address
addrinfo hints;
memset(&hints, 0, sizeof(hints));
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE;

addrinfo *bindAddr;
getaddrinfo(0, "8080", &hints, &bindAddr);
other::PrintIP(bindAddr);

#ifdef _WIN32
// cleanup
    free(adapters);
    WSACleanup();
#endif
}
