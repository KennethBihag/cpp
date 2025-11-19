#include "endpoint.h"

#include <iostream>

using std::cerr; using std::clog;

EndPoint::EndPoint(const sockaddr *sa, int len){
	if(!sa || len < 1){
		cerr << __func__ << ": invalid arguments\n";
		exit(EXIT_FAILURE);
	}
	int error = getnameinfo(sa, len, m_host, sizeof(m_host), m_service, sizeof(m_service),
													NI_NUMERICHOST|NI_NUMERICSERV);
	if(error){
		cerr << __func__ << ": getnameinfo failed\n";
		exit(error);
	}
}