#include "networking.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>

#include "logger.h"

#include "usings.h"

unordered_map<int, string> g_familyMap = {
    {AF_INET, "IPv4"}, {AF_INET6, "IPv6"}, {AF_UNSPEC, "ANY"}
};
unordered_map<int, string> g_sockMap = {
    {SOCK_DGRAM, "UDP"}, {SOCK_STREAM, "TCP"}, {0, "ANY"}
};
unordered_map<int, string> g_protoMap = {
    {IPPROTO_UDP, "UDP PROTO"}, {IPPROTO_TCP, "TCP PROTO"}, {0, "ANY"}
};
unordered_map<int, string> g_flagMap = {
    {AI_ALL, "ALL"}, {AI_PASSIVE, "PASSIVE"}, {0, "NONE"}
};

#ifdef _WIN32
int StartUp(WSADATA& wdData){
    if(WSAStartup(MAKEWORD(2,2), &wdData)){
        cerr << "WSAStartup failed!\n";
        return WSAGetLastError();
    }
#else
int StartUp(){
#endif // _WIN32
    cout << "StartUp():Success\n";
    return EXIT_SUCCESS;
}

void CleanUp(){
#ifdef _WIN32
    int iRes = WSACleanup();
#else
    int iRes = EXIT_SUCCESS;
#endif
    clog << "CleanUp():" << iRes << "\n";
}

void ThrowError(const string& p_msg, int p_code) {
    stringstream ssTmp;
    ssTmp << p_msg << " " << p_code;
    throw runtime_error(ssTmp.str());
}

void ThrowNetworkError(const string& p_msg) {
    ThrowError(p_msg, GETSCKERR());
}

stringstream FileAsSStream(const char *fpath){
    ifstream ifsRequest(fpath,std::ios::in|std::ios::binary);
    if(!ifsRequest)
        throw runtime_error("Could not open file!");
    stringstream ssRequest;
    ssRequest << ifsRequest.rdbuf();
    return ssRequest;
}
