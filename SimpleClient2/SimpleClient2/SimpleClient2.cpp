// SimpleClient.cpp : Defines the entry point for the console application.
//

//connet to news.zing.vn
// nc: nc.exe -v news.zing.vn 80
//go vao "GET /HTTP/1.1"
//go vao "Host: news.zing.vn" enter 2 lan


#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "winsock2.h"
#include "ws2tcpip.h"

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);  // start winsock

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //tao socket

	SOCKADDR_IN addr; // tao cau truc dia chi
	//addr.sin_family = AF_INET; //xet IP v4
	//addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //tao dia chi server==> doi lai cong khi chay den web cu the
	//addr.sin_port = htons(9000); // tao cong ket noi

	//doan nay de phan giai ten mien
	addrinfo *result;
	int res;
	res = getaddrinfo("news.zing.vn", "http", NULL, &result);
	if (res == 0)
		memcpy(&addr, result->ai_addr, sizeof(addr));
	else
	{
		printf("Phan giai dia chi thanh cong\n");
		return 1;
	}

	connect(client, (SOCKADDR *)&addr, sizeof(addr)); //connect

	char *msg = "GET /HTTP/1.1\n Host: news.zing.vn\n\n";
	//char *msg = "Hello Server";

	send(client, msg, strlen(msg), 0);

	char buf[1024];
	//	int res;
	while (true)
	{
		res = recv(client, buf, sizeof(buf), 0);
		if (res == SOCKET_ERROR || res == 0)
			break;
		//them ki tu ket thuc xau ra man hinh
		if(res < 1024)
			buf[res] = 0;
		printf("%s", buf);
	}


	closesocket(client);
	WSACleanup();

	system("pause");

	return 0;
}


