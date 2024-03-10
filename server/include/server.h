#ifndef SERVER_H
#define SERVER_H

// sockets
#ifdef _WIN32
#include <winsock2.h>
#endif

#define MAX_CLIENTS 10

extern SOCKET svSock;
extern struct sockaddr_in svAdd;

int create_connection(const char host[], int port);
SOCKET accept_client();
int get_data(SOCKET clSock, const char msg[], int len);
int send_data(SOCKET clSock, const char msg[], int len);
void close_connection(SOCKET clients[]);

// html request, response
#define MAX_RESP_LEN 1024

extern char g_request[MAX_RESP_LEN];
extern char g_response[MAX_RESP_LEN];
extern char g_css_init_resp[];
void create_html_body(const char *const body);
#endif