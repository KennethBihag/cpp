#ifndef ENDPOINT_H
#define ENDPOINT_H

#include "common.h"

struct EndPoint {
  EndPoint() = default;
  EndPoint(const sockaddr *sa, int len);
  char m_host[64]{};
  char m_service[64]{};
};

#endif