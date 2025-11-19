#include "config.h"

Config::~Config(){
  if(m_result)
    freeaddrinfo(m_result);
}