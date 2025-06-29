#include <iostream>

#include "interfaces.h"
#include "connection.h"

#include "colored_console.h"
#include "common.h"

using namespace std;
using namespace HydraExpert;

const char *getMsg = R"(GET / HTTP/1.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate, br, zstd
Accept-Language: en-US,en;q=0.9
Cache-Control: max-age=0
Connection: keep-alive
If-Modified-Since: Fri, 07 Mar 2025 12:38:16 GMT
If-None-Match: W/"976-195709d10c6"
Sec-Fetch-Dest: document
Sec-Fetch-Mode: navigate
Sec-Fetch-Site: same-origin
Sec-Fetch-User: ?1
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/137.0.0.0 Safari/537.36 Edg/137.0.0.0
sec-ch-ua: "Microsoft Edge";v="137", "Chromium";v="137", "Not/A)Brand";v="24"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "Windows"

)";

int main(int argc, const char **argv){
    WSADATA wdData;
    StartUp(wdData);
    try
    {
        string host(""), port("");
        int fam = AF_UNSPEC;
        int sockType = 0;
        int flags = AI_PASSIVE | AI_ALL;

        switch(argc){
            case 6:
                flags = atoi(argv[5]);
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

        // cout << Interfaces::GetInterfaces();
        Client client(host, port, fam, sockType);
        cout << client.GetAddrInfoStr();
        cout << "*******\n";
        cout << client.GetSockInfoStr() <<"\n";
        client.Activate();
        cout << client.GetSockInfoStr() << "\n";
        char buff[g_rcvLim]{};
        sprintf(buff, "%s", getMsg);
        cout << "Sent: " << client.Send(buff, 128) << " bytes\n";
        memset(buff, 0, g_rcvLim);
        cout << "Received: " << client.Receive(buff) << " bytes\n";
        ColoredConsole(Console::GRN, cout, buff);
    }
    catch(...){
        cerr << "Oooops!\n";
    }

    CleanUp();
}