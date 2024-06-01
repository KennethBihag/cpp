#include "splitnmerge.hpp"
#include <cmath>

using namespace std;

const long long g_byteLimit = 512LL;

fpos_t GetFileSize(const string& inPath){
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
        cout << (toSkip.state()._Wchar+1) << ":" << toRead
             << ":" << inPath << ":" << outPath << endl;
        inFile.seekg(toSkip, ios::beg);
        char buffer[g_byteLimit];
        while (toRead > 0) {
            const streamsize bytesRead = min(toRead, g_byteLimit);
            inFile.read(buffer, bytesRead);
            outFile.write(buffer, bytesRead);
            toRead -= bytesRead;
        }
        inFile.close();
        outFile.close();
    }
}