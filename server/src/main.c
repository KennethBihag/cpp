#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _WIN32
#define INVALID_SOCKET -1
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

	FILE *fp = fopen("./styles.css", "r");
	if (!fp)
	{
		fprintf(stderr, "Could not open css file\n");
	}
	char css_content[64] = {0};
	fread(css_content, 1, 63, fp);
	fclose(fp);

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
	closesocket(clients[0]);

	clients[0] = accept_client();
	get_data(clients[0], g_request, strlen(g_request));
	send_data(clients[0], g_css_init_resp, strlen(g_css_init_resp));
	closesocket(clients[0]);

	clients[0] = accept_client();
	get_data(clients[0], g_request, strlen(g_request));
	send_data(clients[0], css_content, strlen(css_content));

	printf("closing connection...\n");
	close_connection(clients);
	return ret;
}