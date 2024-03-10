#include <server.h>

#include <stdio.h>
#include <string.h>

char g_response[MAX_RESP_LEN] = "";
char g_request[MAX_RESP_LEN] = "";

const char html_resp[] =
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"\r\n"
	"<html>";
const char endhtml[] = "</html>\r\n";

void create_html_body(const char *const body)
{
	g_response[0] = '\0';
	int msgLen = strlen(html_resp) + strlen(endhtml);
	const int maxBodyLen = MAX_RESP_LEN - msgLen - 1;
	strcat(g_response, html_resp);
	strncat(g_response, body, maxBodyLen);
	strcat(g_response, endhtml);
}