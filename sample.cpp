#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct MyObject
{
	char pet[8];
	unsigned short weight;
	bool good;
};

int main(int argc, const char **argv)
{
	printf("START main\n");
	FILE *fp;
	const int MyObjectLen = sizeof(MyObject);

	if (argc < 2)
	{
		MyObject mo1 =
			{
				.pet = "cat",
				.weight = 45,
				.good = true};

		fp = fopen("myobject.mo", "w");
/* 		char *mp = (char*)&mo1;
		for(int i=0; i<MyObjectLen; ++i)
			fprintf(fp, "%c", mp+i); */
		fwrite(&mo1, 1, MyObjectLen, fp);
	}
	else
	{
		const char *fn = argv[1];
		fp = fopen(fn, "r");
		char myobjbuff[MyObjectLen]={0};
		fread(myobjbuff, 1, MyObjectLen, fp);
		MyObject *mo1 = (MyObject*)myobjbuff;
		printf("MyObject read from file:\n");
		printf("\t%s\n\t%hu\n\t%hi\n",
			mo1->pet, mo1->weight, mo1->good);
	}

	fclose(fp);

	printf("END main\n");
	return EXIT_SUCCESS;
}
