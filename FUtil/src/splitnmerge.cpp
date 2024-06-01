#include "splitnmerge.hpp"
#include <pthread.h>
#include <cmath>

using namespace std;

const long long g_byteLimit = 512LL;
pthread_mutex_t mtx;

#ifdef _WIN32
fpos_t
#else
long long
#endif
GetFileSize(const string& inPath){
    ifstream inFile(inPath, ios::in | ios::binary);
    if(inFile.is_open()){
        auto start = inFile.tellg();
        inFile.seekg(0, ios::end);
        return inFile.tellg() - start;
    } else
        return -1;
}

void CpyFBytesToF(const string& inPath,
  const string& outPath, streampos toSkip,
  streamsize toRead, int app){

    ifstream inFile(inPath, ios::in | ios::binary);
    ofstream outFile;
    if(app)
        outFile.open(outPath, ios::out | ios::app | ios::binary);
    else
        outFile.open(outPath, ios::out | ios::binary);
    if(inFile.is_open() && outFile.is_open()) {
pthread_mutex_lock(&mtx);
#ifdef _WIN32
        cout << (toSkip.state()._Wchar+1)
#else
        cout << (toSkip.state().__count+1)
#endif
             << ":" << toRead
             << ":" << inPath << ":" << outPath << endl;
pthread_mutex_unlock(&mtx);
        inFile.seekg(toSkip, ios::beg);
        char buffer[g_byteLimit];
        while (toRead > 0) {
            const streamsize bytesRead = min((long)toRead, (long)g_byteLimit);
            inFile.read(buffer, bytesRead);
            outFile.write(buffer, bytesRead);
            toRead -= bytesRead;
        }
        inFile.close();
        outFile.close();
    }
}