#include <Windows.h>

#include <iostream>

#define BUFFER_LENGTH 1023
using namespace std;

int main(){
    /*
    PHANDLE hRead, hWrite;
    char szBuffer[512] = "hello pipe";
    DWORD dwBufferSize = sizeof(szBuffer);
    BOOL bReadfile;
    BOOL bWritefile;
    DWORD dwNoBytesWrite;
    DWORD dwNoBytesRead;
    BOOL bCreatePipe = CreatePipe(hRead,hWrite,NULL,dwBufferSize);
    if(bCreatePipe == FALSE)
        cout << "Create pipe error : " << GetLastError() << endl;
    else cout << "created pipe successfully\n";
    
    bWritefile = WriteFile(hWrite,szBuffer,dwBufferSize,&dwNoBytesWrite,NULL);

    CloseHandle(hWrite);

    bReadfile = ReadFile(hRead,szBuffer,dwBufferSize,&dwNoBytesRead,NULL);
    CloseHandle(hRead);

    cout << "Read frm Pipe - " << szBuffer << endl;
    */ /**/

    char szBuffer[BUFFER_LENGTH] = "hello pipe";
    DWORD dwBufferSize = sizeof(szBuffer);
    BOOL bWritefile;
    DWORD dwNoBytesWrite;
    HANDLE namedPipe;
    BOOL isConnected;
    char iBuffer[BUFFER_LENGTH];
    char oBuffer[BUFFER_LENGTH];
    DWORD oBufferSize = sizeof(oBuffer);
    DWORD iBufferSize = sizeof(iBuffer);

    namedPipe = CreateNamedPipeW(L"\\\\.\\pipe\\myNamedPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        oBufferSize,
        iBufferSize,
        NULL,
        NULL
    );
    if(namedPipe == INVALID_HANDLE_VALUE)
        cout << "Error : " << GetLastError() << endl;

    isConnected = ConnectNamedPipe(namedPipe,NULL);
    if (isConnected == FALSE)
        cout << "Not connected : " << GetLastError() << endl;
    bWritefile = WriteFile(namedPipe,szBuffer,dwBufferSize,&dwNoBytesWrite,NULL);
    BOOL flushedFile = FlushFileBuffers(namedPipe);

    DisconnectNamedPipe(namedPipe);
    CloseHandle(namedPipe);
    return 0;
}