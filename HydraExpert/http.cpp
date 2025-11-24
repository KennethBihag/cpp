#include "http.h"

#include <fstream>
#include <iostream>
#include <string.h>
#include <unordered_map>

#include "hydra_expert.h"

using namespace std;

extern string gRootPath;

namespace HTTP
{
    const char *const m_Template =
        "HTTP/1.1 200 OK\r\n"
        "Access-ranges: bytes\r\n"
        "Content-type: text/html; charset=UTF-8\r\n"
        "Content-length: ";

    const char *const g_Template0 =
        "HTTP/1.1 200 OK\r\n"
        "Access-ranges: bytes\r\n"
        "Content-length: ";

    const char *const m_NotFound =
        "HTTP/1.1 404 NOT FOUND\r\n\r\n";

    const char *const s_delim = "\r\n";
    const char *const s_end = "\r\n\r\n";

    const unordered_map<string, Method> g_MethodMap = {
        {"GET", GET}, {"POST", POST}, {"PUT", PUT}};

    string GetDoc(const string &path)
    {
        ifstream docStrm(gRootPath + path, ios_base::binary);
        if (!docStrm.is_open())
            return m_NotFound;
        docStrm.seekg(0, ios_base::end);
        long long sz = docStrm.tellg();
        docStrm.seekg(0);
        char *bf = new char[sz + 1]{0};
        int i = 0;
        char c;
        while ((c = (char)docStrm.get()) != EOF)
            bf[i++] = c;
        docStrm.close();
        string ret;
        if (path.find_last_of(".html") == path.length() - 5)
            ret.assign(m_Template);
        else
            ret.assign(g_Template0);
        ret += to_string(sz);
        ret += "\r\n\r\n";
        ret += bf;
        return ret;
    }

    string GetIndexDoc()
    {
        return GetDoc("/index.html");
    }

    Request::Request(const char *msg, int len)
        : m_raw(msg), m_valid(false)
    {
        const unsigned char lineSz = 128;
        const unsigned char tokSz = lineSz/3;
        const unsigned char t2Pos = tokSz,
                            t3pos = t2Pos + tokSz;
        char line[lineSz]{};
        char tokens[lineSz]{};
        m_raw.getline(line, lineSz-1);
        char fmt[32];
        snprintf(fmt, sizeof(fmt), "%%%hus %%%hus %%%hus\r",
            tokSz, tokSz, tokSz);
        sscanf(line, fmt, tokens, tokens+t2Pos, tokens+t3pos);
        clog << line << endl;
        m_method = g_MethodMap.at(tokens);
        m_path.assign(tokens+t2Pos);
        if(strcmp((tokens+t3pos),"HTTP/1.1")){
            cerr << "Protocol " << (tokens+t3pos) << " unrecognized\n";
            return;
        }

        char *key = tokens, *val = tokens+t2Pos;
        snprintf(fmt, sizeof(fmt), "%%%hu[-a-zA-Z]: %%%hus\r", tokSz, tokSz*2);
        memset(line, 0, lineSz);
        while(m_raw.getline(line, lineSz-1)){
            int ret = sscanf(line, fmt, key, val);
            if(ret < 2){
              cerr << "Error parsing request\n";
              return;
            }
            if(strcasecmp(key,"host")==0) {
              m_host.assign(val);
            } else if(strcasecmp(key,"connection")){
              strcasecmp(val,"keep-alive")==0 ?
                m_keepAlive=true : m_keepAlive=false;
            }
            memset(line, 0, lineSz);
            memset(tokens, 0, sizeof(tokens));
        }
        m_valid = true;
    }
}