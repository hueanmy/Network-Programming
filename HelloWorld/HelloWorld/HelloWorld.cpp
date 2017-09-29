#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>

void main()
{
	WSADATA DATA;
	int error = WSAStartup(MAKEWORD(2, 2), &DATA);
	if (error != 0)
		return;
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		int ecode = WSAGetLastError();
		printf("%d\n", ecode);
		return;
	}
	SOCKADDR_IN saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(80);
	saddr.sin_addr.S_un.S_addr = inet_addr("192.168.0.1");
	InetPton(AF_INET, L"192.168.0.1", &(saddr.sin_addr.S_un.S_un_b));
	PADDRINFOA result;
	getaddrinfo("www.google.com", "http", NULL, &result);
	PADDRINFOA tmp = result;
	while (tmp != NULL)
	{
		memcpy(&saddr, tmp->ai_addr, tmp->ai_addrlen);
		printf("%s", inet_ntoa(saddr.sin_addr));
		tmp = tmp->ai_next;
	}
}