#include <iostream>

#include "interfaces.h"
#include "connection.h"

#include "logger.h"
#include "common.h"

using namespace std;
using namespace HydraExpert;

namespace HydraExpert{
    char log[1024];
}

int main(int argc, const char **argv){
    WSADATA wdData;
    StartUp(wdData);
    try
    {
        string host(""), port("");
        int fam = AF_UNSPEC;
        int sockType = 0;

        switch(argc){
            case 5:
                {
                    string tmp = argv[4];
                    if((tmp == "t") | (tmp == "T"))
                        sockType = SOCK_STREAM;
                    else if((tmp=="u") | (tmp=="U"))
                        sockType = SOCK_DGRAM;
                    else
                        sockType = 0;
                }
            case 4:
                {
                    string tmp = argv[3];
                    if((tmp == "v4") | (tmp == "V4"))
                        fam = AF_INET;
                    else if((tmp=="v6") | (tmp=="V6"))
                        fam = AF_INET6;
                    else
                        fam = AF_UNSPEC;
                }
            case 3:
                port = argv[2];
            case 2:
                host = argv[1];
            break;
        }

        IConnection &&server = Server(host, port, fam, sockType);
        Logger::Log(Logger::Inf, "Config", server.GetAddrInfoStr());
        Logger::Log(Logger::Inf, "Socket", server.GetSockInfoStr());
        server.Activate();
        Logger::Log(Logger::Out, "Bound and Listening", server.GetSockInfoStr());

    }
    catch(const runtime_error& err){
        string errStr(err.what());
        errStr += "\n";
        ColoredConsole(Console::RED, cerr, errStr.c_str());
    }

    CleanUp();
}