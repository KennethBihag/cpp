#include "common/include/tests.h"
#include "common/include/sort.h"
#include "common/include/common.h"

#include <iostream>
using namespace std;

int main(int argc, const char *argv[])
{
	bubblesort_test(argc, argv);
	mergesort_test(argc,argv);
	cout << "Testing mergesort_int" << endl;
	int sample[] = {0,1,2,3,4,-5,-6,-7,8,2};
	cout << "-------------------------------\n";
	cout << "Sample: ";
	print_intarr_elems(sample,sizeof(sample)/sizeof(int));
	mergesort_int(sample,sizeof(sample)/sizeof(int));
	print_intarr_elems(sample,sizeof(sample)/sizeof(int));
	
	return 0;
}
