#ifndef HYDRA_EXPERT_H
#define HYDRA_EXPERT_H

#include <string>

struct HydraExpert {
	enum Family {ANY, IPV4, IPV6};
	HydraExpert(std::string host, std::string service, unsigned short backLog,
							int millisTimeout, Family family = IPV4);
	~HydraExpert();
  void Start();
};

#endif