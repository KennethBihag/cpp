#include "server.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#define SOCKET_ERROR -1
#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

SOCKET svSock = 0;
sockaddr_in svAdd = {0};

#ifndef _WIN32
inline int closesocket(SOCKET s){
	return close(s);
}
#endif

int create_connection(const char host[], int port)
{
#ifdef _WIN32
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		fprintf(stderr, "WSAStartup failed\n");
		return EXIT_FAILURE;
	}
	svSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (svSock == INVALID_SOCKET)
	{
		fprintf(stderr, "Failed to start server.\n");
		WSACleanup();
		return EXIT_FAILURE;
	}
	printf("Server(%llu) started\n", svSock);
	svAdd.sin_family = AF_INET;
	svAdd.sin_addr.s_addr = inet_addr(host);
	svAdd.sin_port = htons(port);
	if (bind(svSock, (sockaddr *)&svAdd, sizeof(svAdd)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Bind failed\n");
		closesocket(svSock);
		WSACleanup();
		return EXIT_FAILURE;
	}
	if (listen(svSock, MAX_CLIENTS) == SOCKET_ERROR)
	{
		fprintf(stderr, "Listen failed\n");
		closesocket(svSock);
		WSACleanup();
		return 1;
	}
#else
    svSock = socket(AF_INET, SOCK_STREAM, 0);
	if(svSock < 0){
		fprintf(stderr, "Failed to start server.\n");
		return EXIT_FAILURE;
	}
	else
	printf("Started server on %d.\n", svSock);

	struct protoent *pe = getprotoent();
	printf("Protocol is %s\n", pe->p_name);

    svAdd.sin_family = AF_INET;
    svAdd.sin_port = htons(port);
    // servAddr.sin_addr.s_addr = INADDR_ANY;
	inet_pton(AF_INET, host, &svAdd.sin_addr);

    if (bind(svSock, (struct sockaddr*)&svAdd, sizeof(svAdd)) == -1) {
        fprintf(stderr, "Bind failed\n");
        close(svSock);
        return EXIT_FAILURE;
    }

    if (listen(svSock, 1) == -1) {
        perror("Listen failed\n");
        close(svSock);
        return EXIT_FAILURE;
    }
#endif
	printf("Listening on %s:%d\n", host, port);
	return EXIT_SUCCESS;
}

SOCKET accept_client()
{
	SOCKET clSock;
	sockaddr_in clAdd;
	int addLen = sizeof(clAdd);
#ifdef _WIN32
	clSock = accept(svSock, (sockaddr *)&clAdd, &addLen);
	if (clSock == INVALID_SOCKET){
		fprintf(stderr, "Accept failed: %d\n", WSAGetLastError());
		return EXIT_FAILURE;
	}
	printf("Client(%llu) connected\n", clSock);
#else
	clSock = accept(svSock, (struct sockAddr*)&clAdd, &addLen);
	if (clSock == -1){
		fprintf(stderr, "Accept failed\n");
		return EXIT_FAILURE;
	}
	printf("Client(%d) connected\n", clSock);
#endif
	return clSock;
}

int get_data(SOCKET clSock, const char msg[], int len)
{
	g_request[0] = '\0';
	int bytesReceived = recv(clSock, g_request, MAX_RESP_LEN, 0);
	if (bytesReceived == SOCKET_ERROR)
	{
#ifdef _WIN32
		fprintf(stderr, "Receive failed: %d\n", WSAGetLastError());
#else
		fprintf(stderr, "Received failed\n");
#endif
		closesocket(clSock);
		return bytesReceived;
	}

	printf("Received request from sock(%llu): %s\n",
		   clSock,
		   g_request);
	return bytesReceived;
}

int send_data(SOCKET clSock, const char msg[], int len)
{
	int ret = 0;
	if ((ret = send(clSock, msg, len, 0)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Send failed\n");
		closesocket(clSock);
	}
	return ret;
}

void close_connection(SOCKET clients[])
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i] != 0)
		{
			closesocket(clients[i]);
		}
	}
	closesocket(svSock);
#ifdef _WIN32
	WSACleanup();
#endif
}