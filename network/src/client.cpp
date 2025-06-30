#include <iostream>

#include "interfaces.h"
#include "connection.h"

#include "logger.h"
#include "common.h"

using namespace std;
using namespace HydraExpert;

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

        IConnection &&client = Client(host, port, fam, sockType);

        Logger::Log(Logger::Inf, "Config", client.GetAddrInfoStr());
        Logger::Log(Logger::Inf, "Socket", client.GetSockInfoStr());
        client.Activate();
        Logger::Log(Logger::Out, "Connected", client.GetSockInfoStr());

        char buff[g_rcvLim]{};
        stringstream ssTmp = FileAsSStream("S:/cpp/network/resource/get.txt");
        size_t ssTmpSz = GetStreamSize(ssTmp);
        ssTmp.read(buff, g_rcvLim-1);
        ssTmp.str(""); ssTmp.clear();
        int bytes = client.Send(buff, strlen(buff));
        ssTmp << bytes << " bytes\n";
        Logger::Log(Logger::Out, "Sent", ssTmp.str());

        memset(buff, 0, g_rcvLim);
        bytes = client.Receive(buff);
        ssTmp.str(""); ssTmp.clear();
        ssTmp << bytes << " bytes\n";
        ssTmp << buff;
        Logger::Log(Logger::Out, "Received", ssTmp.str());
    }
    catch(const runtime_error& err){
        Logger::Log(err);
    }

    CleanUp();
}