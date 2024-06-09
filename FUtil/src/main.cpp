#include <pthread.h>
#include <string.h>

#include <fstream>
#include <iostream>
#include <string>

#include "cryptographer.hpp"
#include "printer.hpp"
#include "splitnmerge.hpp"

using namespace std;

void *CpyThread(void *arg);
struct CpyThrdArg{
    string inpath;
    string outpath;
    long long offset;
    long long bytes;
};

int main(int argc, const char *argv[]){
    if(argc<4){
        cout << "USAGE: " << argv[0]
             << " <<split|merge> <file path> [parts]"
             << " | crypt <file path> <password>>"
             << endl;
        return EXIT_FAILURE;
    }

    string comm(argv[1]);
    string inpath(argv[2]);
    long long parts = 0;
    size_t t = inpath.find_last_of("\\/");
    string leaf = inpath.substr(t+1);
    string indir(inpath);
    indir.erase(indir.length()-leaf.length());

    if(comm.compare("split")==0 || comm.compare("merge")==0){
        parts = atoll(argv[3]);
        if(parts < 2)
            return EXIT_FAILURE;
    }

    if(comm.compare("split")==0){
        long long fileSz = GetFileSize(inpath);
        if(fileSz < 0)
            return EXIT_FAILURE;
        long long chunkSz = fileSz/parts;
        if(chunkSz < 1)
            return EXIT_FAILURE;
        
        pthread_t *ts = new pthread_t[parts];
        CpyThrdArg *args = new CpyThrdArg[parts];
        for(int id=0; id<parts; id++){
            char prefix[4];
            sprintf(prefix, "%hhd", id);
            string outpath(indir);
            outpath.append(prefix).append("_").append(leaf);
            long long offSet = id*chunkSz;
            if(id==parts-1){
                chunkSz = fileSz - id*chunkSz;
            }
            args[id] = CpyThrdArg{inpath, outpath, offSet, chunkSz};
        }

        for(int i=0; i<parts; i++){
            pthread_create(ts+i, NULL, CpyThread, args+i);
        }

        for(int i=0; i<parts; i++){
            pthread_join(ts[i], NULL);
        }

        delete [] ts;

    } else if(comm.compare("merge")==0){
        string outpath(indir);
        outpath.append("merged").append("_").append(leaf);
        for(int id=0; id<parts; id++){
            char prefix[4];
            sprintf(prefix,"%hhd",id);
            string part(indir);
            part.append(prefix).append("_").append(leaf);
            auto pfsz = GetFileSize(part);
            CpyFBytesToF(part, outpath, 0, pfsz, 1);
        }
    } else if(comm.compare("crypt")==0){

        Cryptographer c(inpath.c_str(), argv[3]);
        string outpath(inpath);
        outpath.append(".ken");
        ofstream ofs(outpath,ios::binary|ios::out);
        Printer p(c,ofs);
        c.GetOrigBytes();
        c.ToggleEncryption();
        p.Print();
        ofs.close();
    } else {
        cout << "NOT IMPLEMENTED" << endl;
    }

    return EXIT_SUCCESS;
}

void *CpyThread(void *arg){
    CpyThrdArg &args = (*(CpyThrdArg*)arg);
    CpyFBytesToF(args.inpath, args.outpath, args.offset, args.bytes);
    return 0;
}