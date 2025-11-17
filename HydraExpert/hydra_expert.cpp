#include "hydra_expert.h"
#include "networking.h"

#include <iostream>
#include <stdexcept>
#include <string>

using std::clog;
using std::runtime_error;
using std::string;

WSAData gWSAData;

HydraExpert::HydraExpert(){
	if(WSAStartup(MAKEWORD(2,2), &gWSAData)){
		int wsaErr = WSAGetLastError();
		string errStr = "WSAStartup failed! Code:";
		errStr += std::to_string(wsaErr);
		throw runtime_error(errStr);
	}
}

HydraExpert::~HydraExpert(){
	WSACleanup();
}

HydraExpert::HydraExpert(std::string host, std::string service,
  unsigned short backLog, unsigned short millisTimeout, Family eFamily)
 : HydraExpert()
{
  int family;
  switch(eFamily){
    case Family::ANY: family = AF_UNSPEC; break;
    case Family::IPV4: family = AF_INET; break;
    case Family::IPV6: family = AF_INET6; break;
  }
  Server server(host, service, family, SOCK_STREAM, backLog, millisTimeout);
}