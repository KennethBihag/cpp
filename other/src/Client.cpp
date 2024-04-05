#include <Windows.h>

#include <iostream>

#define BUFFER_LENGTH 1023
using namespace std;

int main(){

    HANDLE namedPipe;
    char iBuffer[BUFFER_LENGTH];
    char oBuffer[BUFFER_LENGTH];
    DWORD oBufferSize = sizeof(oBuffer);
    DWORD iBufferSize = sizeof(iBuffer);
    DWORD readBytes;

    namedPipe = CreateFile("\\\\.\\pipe\\myNamedPipe",
        GENERIC_READ | GENERIC_WRITE,
        NULL,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(namedPipe == INVALID_HANDLE_VALUE)
        cout << "Error : " << GetLastError() << endl;
    BOOL readFile = ReadFile(namedPipe,iBuffer,iBufferSize,&readBytes,NULL);

    cout << "Read from server : "<< iBuffer << endl;

    return 0;
}