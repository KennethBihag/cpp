#ifndef HTTP_H
#define HTTP_H

#include <sstream>
#include <unordered_map>

namespace HTTP {
  enum Method {GET, POST, PUT};
  extern const char *const m_Template;
  extern const char *const m_NotFound;
  extern std::string GetIndexDoc();
  extern std::string GetDoc(const std::string&);
  extern const char *const s_delim;
  extern const char *const s_end;
  using SMMap = std::unordered_map<std::string, Method>;
  extern const  SMMap g_MethodMap;
  struct Request {
    Request(const char*, int);
    std::stringstream m_raw;
    Method m_method;
    std::string m_host;
    std::string m_path;
    std::stringstream m_body;
    bool m_keepAlive;
    bool m_valid;
  };
};

#endif