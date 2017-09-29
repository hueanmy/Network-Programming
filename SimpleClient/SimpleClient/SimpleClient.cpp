// SimpleClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);  // start winsock

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //tao socket

	SOCKADDR_IN addr; // tao cau truc dia chi
	addr.sin_family = AF_INET; //xet IP v4
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //tao dia chi server
	addr.sin_port = htons(9000); // tao cong ket noi

	connect(client, (SOCKADDR *)&addr, sizeof(addr)); //connect
	char *msg = "Hello Server";

	send(client, msg, strlen(msg), 0);

	char buf[1024];
	int res;
	while (true)
	{
		res = recv(client, buf, sizeof(buf), 0);
		if (res == SOCKET_ERROR || res == 0)
			break;
		//them ki tu ket thuc xau ra man hinh
		buf[res] = 0;
		printf("%s", buf);
	}


	closesocket(client);
	WSACleanup();

	return 0;
}

