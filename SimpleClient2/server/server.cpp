// server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "winsock2.h"


int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8000);

	SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(listener, (SOCKADDR *)&addr, sizeof(addr));
	listen(listener, 5);

	SOCKET client = accept(listener, NULL, NULL);

	char buf[1024];
	int res;
	float f;

	while (true) {
		res = recv(client, buf, sizeof(buf), 0);
		if (res == SOCKET_ERROR || res == 0)
			break;
		//buf[res] = 0;
		//printf("%s", buf);
		printf("%d bytes recvies\n", res);

		memcpy(&f, buf, 4);
		printf("Number: %f\n", f);
	}

	closesocket(client);
	closesocket(listener);
	WSACleanup;
    return 0;
}

