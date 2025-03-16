#include "includes.hpp"
#include <iostream>
using std::cout;

namespace other
{
    void PrintIP(addrinfo *bindAddr)
    {
        cout << "Configured loc: ";
        char ap[128]{};
        getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, ap, sizeof(ap), 0, 0, NI_NUMERICSERV);
        cout << ap << '\n';
    }
};