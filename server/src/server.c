#include "server.h"

#include <stdio.h>
#include <winsock2.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

SOCKET create_connection(const char host[], int port)
{
	WSADATA wsadata;
	SOCKET svSock;
	sockaddr_in svAdd;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		fprintf(stderr, "WSAStartup failed\n");
		return 0;
	}
	svSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (svSock == INVALID_SOCKET)
	{
		fprintf(stderr, "socket failed\n");
		WSACleanup();
		return 0;
	}
	svAdd.sin_family = AF_INET;
	svAdd.sin_addr.s_addr = inet_addr(host);
	svAdd.sin_port = htons(port);

	if (bind(svSock, (sockaddr *)&svAdd, sizeof(svAdd)) == SOCKET_ERROR)
	{
		fprintf(stderr, "Bind failed\n");
		closesocket(svSock);
		WSACleanup();
		return 0;
	}
	printf("Bound address: %s:%d\n", host, port);

	return svSock;
}

SOCKET listen_connection(SOCKET svSock)
{
	SOCKET clSock;
	sockaddr_in clAdd;
	int addLen = sizeof(clAdd);
	printf("Listening...\n");
	if (listen(svSock, MAX_CLIENTS) == SOCKET_ERROR)
	{
		fprintf(stderr, "Listen failed\n");
		closesocket(svSock);
		WSACleanup();
		return 0;
	}
	clSock = accept(svSock, (sockaddr *)&clAdd, &addLen);
	if (clSock == INVALID_SOCKET)
	{
		fprintf(stderr, "Accept failed: %d\n", WSAGetLastError());
		closesocket(svSock);
		WSACleanup();
		return 0;
	}

	char buffer[1024] = {0};
	printf("sizeof(buffer): %d\n", sizeof(buffer));
	int bytesReceived = recv(clSock, buffer, sizeof(buffer), 0);
	if (bytesReceived == SOCKET_ERROR)
	{
		fprintf(stderr, "Receive failed: %d\n", WSAGetLastError());
		closesocket(clSock);
		closesocket(svSock);
		WSACleanup();
		return 0;
	}

	printf("Received request: %s\n", buffer);

	return clSock;
}

int send_data(SOCKET clsock, const char msg[], int len)
{
	if (send(clsock, msg, len, 0) == SOCKET_ERROR)
	{
		fprintf(stderr, "Send failed\n");
		return 1;
	}
	return 0;
}

void close_connection(SOCKET svSock, SOCKET clients[])
{
	closesocket(svSock);
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i] != 0)
		{
			closesocket(clients[i]);
		}
	}
	WSACleanup();
}