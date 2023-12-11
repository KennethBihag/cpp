#include "common/include/common.h"
#include <iostream>

int main(int argc, const char *argv[]){
	switch (argc)
	{
	case 3:
		std::cout << "Second: " << argv[2] << "\n";
	case 2:
		std::cout << "First: "<< argv[1] << "\n";
		break;
	default:
		std::cout << "No args or at least 3 args are given\n";
		break;
	}
	libfunc();
	return 0;
}