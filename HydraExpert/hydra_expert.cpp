#include "hydra_expert.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "networking.h"
#include "server.h"
#include "socket.h"

using std::clog;
using std::string;
using std::unordered_map;

Config *gConfig = nullptr;
Server *gServer = nullptr;
string gRootPath;

static const unordered_map<HydraExpert::Family, int> g_eFamilyMap =
{
	{HydraExpert::ANY, AF_UNSPEC},
	{HydraExpert::IPV4, AF_INET},
	{HydraExpert::IPV6, AF_INET6}
};

HydraExpert::HydraExpert(std::string host, std::string service,
	unsigned short backLog, int millisTimeout, Family eFamily)
{
	Networking::StartUp();
	clog << "StartUp succeeded\n";
	gConfig = Networking::ConfigServer(host, service, g_eFamilyMap.at(eFamily),
																					 SOCK_STREAM, backLog, millisTimeout);
	Socket socket(gConfig);
	clog << "Config succeeded\n";
	socket.Activate(bind);
  clog << "Bind succeeded\n";
  gServer = new Server(socket, backLog);
  clog << "Created server\n";
}

HydraExpert::~HydraExpert() {
	Networking::CleanUp();
}

void HydraExpert::Start(){
  gServer->Start();
  clog << "Started server\n";
  gServer->Process();
}

void HydraExpert::SetRootPath(const string &path) {
  gRootPath = path;
}