#include <server.h>

#include <stdio.h>
#include <string.h>

char g_response[MAX_RESP_LEN] = "";
char g_request[MAX_RESP_LEN] = "";

const char html_resp[] =
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"Connection: close\r\n"
	"\r\n"
	"<html><head><link href='./styles.css' rel=stylesheet></head>";
const char endhtml[] = "</html>\r\n";

char g_css_init_resp[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/css\r\n"
	"Connection: close\r\n"
	"\r\n";

void create_html_body(const char *const body)
{
	g_response[0] = '\0';
	int msgLen = strlen(html_resp) + strlen(endhtml);
	const int maxBodyLen = MAX_RESP_LEN - msgLen - 1;
	strcat(g_response, html_resp);
	strcat(g_response,"<body>");
	strncat(g_response, body, maxBodyLen-13);
	strcat(g_response,"</body>");
	strcat(g_response, endhtml);
}