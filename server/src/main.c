#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <server.h>

int main(const int argc, const char **const argv)
{
	if (argc < 3)
	{
		printf("Usage: <host> <port> [message]\n");
		return EXIT_FAILURE;
	}
	const char *const host = argv[1];
	const int port = atoi(argv[2]);

	if (argc > 3)
	{
		create_html_body(argv[3]);
	}
	else
	{
		create_html_body("Hello World!");
	}
	SOCKET clients[MAX_CLIENTS] = {0};
	SOCKET svsock = create_connection(host, port);
	clients[0] = listen_connection(svsock);
	int ret = send_data(
		clients[0],
		g_response,
		strlen(g_response));
	printf("closing connection...\n");
	close_connection(svsock, clients);
	return ret;
}