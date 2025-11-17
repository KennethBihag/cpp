#ifndef HYDRA_EXPERT_H
#define HYDRA_EXPERT_H

#include <string>

struct HydraExpert {
  enum Family {ANY, IPV4, IPV6};
  HydraExpert();
  ~HydraExpert();
	HydraExpert(std::string host, std::string service, unsigned short backLog,
							unsigned short millisTimeout, Family family = IPV4);
};

#endif