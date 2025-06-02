#include <iostream>

#include "networking.h"
#include "addr.h"

using namespace std;
using namespace KNT;

int main(int argc, const char **argv){
string h, p;
int f = AF_UNSPEC, sockT = 0;

switch(argc){
    case 5:
    {
        string temp(argv[4]);
        sockT = temp=="UDP" ? SOCK_DGRAM :
                temp=="TCP" ? SOCK_STREAM : 0;
    }
    case 4:
    {
        string temp(argv[3]);
        f = temp=="v4" ? AF_INET :
            temp=="v6" ? AF_INET6 : AF_UNSPEC;
    }
    case 3:
        h = argv[2]; p = argv[1];
    break;
    case 2:
    case 1:
            cout << "Usage: client <service name|port> <hostname|IP address> [v4|v6|any]"
                    " [TCP|UDP|any]\n";
            return EXIT_SUCCESS;
}

cout << "Connecting to " <<  h << ":" << p << "\n";
#ifdef _WIN32
    WSADATA wdData;
    StartUp(wdData);
#else
    StartUp();
#endif

// networking
Addr &&client = Client(h,p,f,sockT);
client.PrintInfo();

CleanUp();

    return EXIT_SUCCESS;
}
