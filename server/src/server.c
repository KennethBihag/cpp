#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <winsock2.h>
#endif

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

SOCKET svSock = 0;
sockaddr_in svAdd = {0};

int create_connection(const char host[], int port)
{
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		fprintf(stderr, "WSAStartup failed\n");
		return EXIT_FAILURE;
	}
	svSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (svSock == INVALID_SOCKET)
	{
		fprintf(stderr, "socket failed\n");
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
	printf("Listening on %s:%d\n", host, port);
	return 0;
}

SOCKET accept_client()
{
	SOCKET clSock;
	sockaddr_in clAdd;
	int addLen = sizeof(clAdd);

	clSock = accept(svSock, (sockaddr *)&clAdd, &addLen);
	if (clSock == INVALID_SOCKET){
		fprintf(stderr, "Accept failed: %d\n", WSAGetLastError());
		return clSock;
	}
	printf("Client(%llu) connected\n", clSock);
	return clSock;
}

int get_data(SOCKET clSock, const char msg[], int len)
{
	g_request[0] = '\0';
	int bytesReceived = recv(clSock, g_request, MAX_RESP_LEN, 0);
	if (bytesReceived == SOCKET_ERROR)
	{
		fprintf(stderr, "Receive failed: %d\n", WSAGetLastError());
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
	WSACleanup();
}