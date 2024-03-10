#ifndef SERVER_H
#define SERVER_H

// sockets
#include <winsock2.h>

#define MAX_CLIENTS 10

SOCKET create_connection(const char host[], int port);
SOCKET listen_connection(SOCKET svSock);
int send_data(SOCKET clsock, const char msg[], int len);
void close_connection(SOCKET svSock, SOCKET clients[]);

// html response
#define MAX_RESP_LEN 1024

extern char g_response[MAX_RESP_LEN];

void create_html_body(const char *const body);
#endif