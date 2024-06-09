#include "cryptographer.hpp"

#include <iostream>
#include <string.h>
#include <fstream>

using std::fstream;
using std::ifstream;
using std::ios;
using std::cout; using std::endl;

const int max_file_size = 1024*5;

Cryptographer::Cryptographer(const char *path, const char *pw)
{
    _path = path;
    _key = 0;
    _bytes = nullptr;
    _bytes_read = 0;
    for (int i = 0; i < strlen(pw); i++)
        _key ^= pw[i];
}

void Cryptographer::GetOrigBytes(){
    if(_bytes != nullptr)
        delete [] _bytes;

    _bytes = new char[max_file_size];
    _bytes_read = 0;
    ifstream infile(_path, ios::binary | ios::in);
    while(true){
        if(!infile.read(_bytes + _bytes_read, 1))
            break;
        _bytes_read++;
    }
    infile.close();
}

void Cryptographer::ToggleEncryption(){
    for(int i=0; i<_bytes_read; i++)
        _bytes[i] ^= _key;
}
