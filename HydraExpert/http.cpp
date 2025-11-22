#include "http.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>

#include "hydra_expert.h"

using namespace std;

extern string gRootPath;

/* const char *const HTTP::m_Template = 
R"(HTTP/1.1 200 OK
Host: localhost:8080
Connection: Close
Content-type: text/html; charset=UTF-8

)"; */

namespace HTTP {
const char *const m_Template = 
"HTTP/1.1 200 OK\r\n"
"Content-type: text/html; charset=UTF-8\r\n"
"Content-length: ";

const char *const m_NotFound = 
"HTTP/1.1 404 NOT FOUND\r\n\r\n";

const char *const s_delim = "\r\n";
const char *const s_end = "\r\n\r\n";

const unordered_map<string, Method> g_MethodMap = {
  {"GET", GET}, {"POST", POST}, {"PUT", PUT}
};

string GetDoc(const string &path){
  ifstream docStrm(gRootPath + path, ios_base::binary);
  if(!docStrm.is_open())
    return m_NotFound;
  docStrm.seekg(0,ios_base::end);
  long long sz = docStrm.tellg();
  docStrm.seekg(0);
  char *bf = new char[sz+1]{0};
  int i=0; char c;
  while((c = (char)docStrm.get()) != EOF)
    bf[i++] = c;
  docStrm.close();
  string ret(m_Template);
  ret += to_string( sz );
  ret += "\r\n\r\n";
  ret += bf;
  return ret;
}

string GetIndexDoc() {
  return GetDoc("/index.html");
}

  Request::Request(const char *msg, int len)
  : m_raw(msg)
  {
    clog << __FUNCTION__ << endl;
    string token;

    m_raw >> token;
    clog << "\tMethod:" << token << ",\n";
    m_method = g_MethodMap.at(token);
      switch(m_method){
      case GET:
        m_valid = true;
      break;
      default:
        cerr << "HTTP method not supported\n";
        m_valid = false;
        return;
    }

    m_raw >> m_path;
    clog << "\tDoc:" << m_path << ",\n";
    m_raw >> token;
    clog << "\tProtocol:" << token << ",\n";
    clog << "\tother:\n";
    while(m_raw >> token){
      clog << " " << token;
    }
    clog << endl;
  }
}