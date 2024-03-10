#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#endif

#include <server.h>

SOCKET clients[MAX_CLIENTS] = {0};

void siginthandle(int sig)
{
	printf("Closing server\n");
	close_connection(clients);
	signal(sig, SIG_DFL);
	exit(EXIT_SUCCESS);
}

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
		create_html_body(argv[3]);
	else
		create_html_body("Hello World!");

	signal(SIGINT, siginthandle);

	int ret = create_connection(host, port);
	if (ret != EXIT_SUCCESS)
		return ret;
ACCEPT:
	clients[0] = accept_client();
	if (clients[0] == INVALID_SOCKET)
		goto ACCEPT;
READSOCK:
	ret = get_data(clients[0],
				   g_request,
				   strlen(g_request));

	ret = send_data(
		clients[0],
		g_response,
		strlen(g_response));

	printf("closing connection...\n");
	close_connection(clients);
	return ret;
}