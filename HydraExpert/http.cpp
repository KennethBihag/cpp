#include "http.h"

/* const char *const HTTP::m_Template = 
R"(HTTP/1.1 200 OK
Host: localhost:8080
Connection: Close
Content-type: text/html; charset=UTF-8

)"; */

const char *const HTTP::m_Template = 
R"(HTTP/1.1 200 OK
Content-type: text/html; charset=UTF-8
Content-length: 44

<html><body><p>HydraExpert</p></body></html>)";