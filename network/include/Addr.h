#ifndef ADDR_H
#define ADDR_H

#include <memory>
#include <string>

#include "networking.h"

namespace KNT {
    class Addr {
        friend class Server; friend class Client;
        std::shared_ptr<addrinfo> m_pAi;
    public:
        Addr(const std::string&, const std::string&, int, int, int);
        virtual ~Addr();
        void PrintInfo() const;
        
    };

    class Server: public Addr{
    public:
        Server(const std::string& p = "", const std::string& n = "", int fam = AF_INET, int sockt = SOCK_STREAM);
        ~Server();
    };

    class Client: public Addr{
    public:
        Client(const std::string& n = "localhost", const std::string& p = "8080",
               int fam = AF_INET, int sockt = SOCK_STREAM);
        ~Client();
    };
}


#endif
