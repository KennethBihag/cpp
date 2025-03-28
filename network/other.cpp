#include "includes.hpp"
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using std::clog;
using std::cout;
using std::ifstream;
using std::string;

const string templates::okPath = "templates/response-ok.txt";
namespace other
{
    using templates::okPath;
    string resp_ok;
    void PrintIP(addrinfo *bindAddr)
    {
        cout << "Configured loc: ";
        // char ap[32]{}, bp[32]{}, cp[32]{}, dp[32]{}, ep[32]{};
        // char aq[32]{}, bq[32]{}, cq[32]{}, dq[32]{}, eq[32]{};
        char bp[32]{}, bq[32]{}, dp[32]{}, dq[32]{};
        // getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, ap, sizeof(ap), aq, 32, NI_NOFQDN);
        getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, bp, sizeof(bp), bq, 32, NI_NUMERICHOST);
        // getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, cp, sizeof(cp), cq, 32, NI_NAMEREQD);
        getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, dp, sizeof(dp), dq, 32, NI_NUMERICSERV);
        // getnameinfo(bindAddr->ai_addr, bindAddr->ai_addrlen, ep, sizeof(ep), eq, 32, NI_DGRAM);
        // cout << "ADDR:" << ap << ',' << bp << ',' << cp << ',' << dp << ',' << ep << '\n';
        // cout << "SRVC:" << aq << ',' << bq << ',' << cq << ',' << dq << ',' << eq << '\n';
        clog << "NumericServ: (" << dp << ") (" << dq << ")\n";
        clog << "NumericHost: (" << bp << ") (" << bq << ")\n";
    }

    string &ResponseOk()
    {
        if (resp_ok.empty())
        {
            ifstream infs(okPath.c_str(), std::ios::in);
            while (!infs.eof())
            {
                char buff[128];
                infs.getline(buff, 128);
                resp_ok += buff;
                resp_ok += "\r\n";
            }
            resp_ok += "\r\n";
        }
        return resp_ok;
    }
};