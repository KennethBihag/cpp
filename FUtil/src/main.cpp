#include <iostream>
#include <string>
#include "splitnmerge.hpp"

using namespace std;

int main(int argc, const char *argv[]){
    if(argc<4){
        cout << "USAGE: " << argv[0]
             << " <split|merge> <file path> [parts]"
             << endl;
        return EXIT_FAILURE;
    }

    string comm(argv[1]);
    string inpath(argv[2]);
    long long parts = atoll(argv[3]);
    size_t t = inpath.find_last_of("\\/");
    string leaf = inpath.substr(t+1);
    string indir(inpath);
    indir.erase(indir.length()-leaf.length());

    if(parts < 2)
        return EXIT_FAILURE;
    if(comm.compare("split")==0){
        long long fileSz = GetFileSize(inpath);
        if(fileSz < 0)
            return EXIT_FAILURE;
        long long chunkSz = fileSz/parts;
        if(chunkSz < 1)
            return EXIT_FAILURE;

        for(int id=0; id<parts; id++){
            char prefix[4];
            itoa(id,prefix,10);
            string outpath(indir);
            outpath.append(prefix).append("_").append(leaf);
            long long offSet = id*chunkSz;
            if(id==parts-1){
                chunkSz = fileSz - id*chunkSz;
            }
            CpyFBytesToF(inpath, outpath, offSet, chunkSz);
        }
    } else if(comm.compare("merge")==0){
        string outpath(indir);
        outpath.append("merged").append("_").append(leaf);
        for(int id=0; id<parts; id++){
            char prefix[4];
            itoa(id,prefix,10);
            string part(indir);
            part.append(prefix).append("_").append(leaf);
            auto pfsz = GetFileSize(part);
            CpyFBytesToF(part, outpath, 0, pfsz, 1);
        }
    } else {
        cout << "NOT IMPLEMENTED" << endl;
    }

    return EXIT_SUCCESS;
}