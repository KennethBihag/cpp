#include <iostream>
#include <string>

#include "Addr.h"

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
        h = argv[2];
    case 2:
        if(strcmp("-h",argv[1]) == 0){
            cout << "Usage: server [service name|port] [hostname|IP address] [v4|v6|any]"
                    "[TCP|UDP|any]\n";
            return EXIT_SUCCESS;
        }
        else
            p = argv[1];
}

cout << "Server starting...\n";
#ifdef _WIN32
    WSADATA wdData;
    StartUp(wdData);
#else
    StartUp();
#endif

Addr &&srv = Server(p, h, f, sockT);
srv.PrintInfo();

CleanUp();
cout << "Server stopped.\n";

    return EXIT_SUCCESS;
}
