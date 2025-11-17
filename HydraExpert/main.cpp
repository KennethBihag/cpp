#include <iostream>
#include <string>

#include "hydra_expert.h"

using namespace std;

int main(int argc, char *argv[])
{
	clog << "Hydra Expert 1.0.0\n";
	string host = "";
	string port = "";
	unsigned short backLog = 1;
	unsigned short msTimeout = 500;

	switch (argc)
	{
	case 5:
		msTimeout = (unsigned short)atoi(argv[4]);
	case 4:
		backLog = (unsigned short)atoi(argv[3]);
	case 3:
		port = argv[2];
	case 2:
		host = argv[1];
		break;
	}
	HydraExpert hydraExpert(host, port, backLog, msTimeout, HydraExpert::ANY);
	return EXIT_SUCCESS;
}