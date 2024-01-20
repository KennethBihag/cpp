#include "testapp.hpp"
#ifdef TEST_LIB
#include "common/include/tests.h"
#include "common/include/sort.h"
#include "common/include/common.h"
#endif

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
	cout << "Started testapp..." << endl;
	#ifdef TEST_LIB
	bubblesort_test(argc, argv);
	mergesort_test(argc,argv);
	cout << "Testing mergesort_int" << endl;
	int sample[] = {0,1,2,3,4,-5,-6,-7,8,2};
	cout << "-------------------------------\n";
	cout << "Sample: ";
	print_intarr_elems(sample,sizeof(sample)/sizeof(int));
	mergesort_int(sample,sizeof(sample)/sizeof(int));
	print_intarr_elems(sample,sizeof(sample)/sizeof(int));
	#endif

	{
		TestApp ta;
	}

	
	cout << "testapp ended" << endl;
	return 0;
}
