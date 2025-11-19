#ifndef CONFIG_H
#define CONFIG_H

#include "common.h"

struct Config {
  ~Config();
  addrinfo m_hints = {0};
  addrinfo *m_result = nullptr;
};

#endif