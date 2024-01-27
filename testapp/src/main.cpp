#include "testapp.hpp"
#ifdef TEST_LIB
#include "common/include/tests.h"
#include "common/include/sort.h"
#include "common/include/common.h"
#endif

#include <malloc.h>
#include <stdio.h>
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
	
	cout << "Sizes of pointers:\n";
	printf("char:%lld, short:%lld, int:%lld, long:%lld, long long:%lld,"
		"void:%lld\n",sizeof(char*),sizeof(short*),sizeof(int*),sizeof(long*),
		sizeof(long long*),sizeof(void*));

	char ch = 'x';
	int in = 666;
	long long li = 12345LL;
	const char *streng = "Hello there!";

	void *vps[10];
	void *vpsall = malloc(10*sizeof(void*));
	void **vpsptr = (void**)vpsall;
	unsigned long long *p = (unsigned long long*)vpsall;
	for(int i=1; i<=10; i++){
		switch(i){
		case 1:
			vps[i-1] = &ch;
			p[i-1] = ch;
			break;
		case 2:
			vps[i-1] = &in;
			p[i-1] = in;
			break;
		case 3:
			vps[i-1] = &li;
			p[i-1] = (unsigned long long)li;
			break;
		case 4:
			vps[i-1] = (void*)streng;
			p[i-1] = (unsigned long long)streng;
			break;
		default:
			vps[i-1] = (void*)(i);
			p[i-1] = i*2;
		}
	}

	printf("%X:1:%c\n",vpsall,*(char*)vpsall);
	printf("%X:2:%d\n",vpsall+8,*(int*)(vpsall+8));
	printf("%X:3:%llu\n",vpsall+16,*(unsigned long long*)(vpsall+16));
	char **tch = (char **)(vpsall+24);
	printf("%X:4:%s\n",vpsall+24,*tch);

	cout << "TEST VOID**\n";
	for(int i=0;i<10;++i){
		printf("%d ADDR:%X\n",i+1,vpsptr+i);
		printf("\tVALUE:%llu\n",(unsigned long long)vpsptr[i]);
		printf("\t\tVALUE2:%llu\n",*(vpsptr+i));
		if(i==3){
			printf("\t\t\t%s\n",vpsptr[i]);
		}
	}

	cout << "testapp ended" << endl;
	return 0;
}
