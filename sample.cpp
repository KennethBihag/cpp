#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, const char **argv)
{
	printf("START main\n");

    if(argc<3)
        return EXIT_FAILURE;

    string inpath(argv[1]);
    int parts;

    sscanf_s(argv[2], "%d", &parts);
    ifstream ifs(inpath, ios::binary | ios::in);
    auto begPos = ifs.tellg();
    ifs.seekg(0,ios::end);
    auto endPos = ifs.tellg();
    auto fsize = endPos-begPos;
    long long psize = fsize/parts;

    char **bfs = new char*[parts];
    ifs.seekg(0,ios::beg);
    int i=0;
    char outpath[64];
    for(; i<parts-1; i++){
        bfs[i] = new char[psize];
        sprintf_s(outpath, "%s.part.%d",
          inpath.c_str(), i+1);
        ofstream ofs(outpath, ios::out | ios::binary);
        ifs.read(bfs[i], psize);
        ofs.write(bfs[i], psize);
        ofs.close();
    }

    psize = fsize - psize*i;
    bfs[i] = new char[psize];
    sprintf_s(outpath, "%s.part.%d",
            inpath.c_str(), i+1);
    ofstream ofs(outpath, ios::out | ios::binary);
    ifs.read(bfs[i], psize);
    ofs.write(bfs[i], psize);
    ofs.close();

    ifs.close();
    for(int i=0; i<parts; i++)
        delete bfs[i];
    delete [] bfs;

	printf("END main\n");
	return EXIT_SUCCESS;
}