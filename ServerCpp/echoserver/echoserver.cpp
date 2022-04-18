/*
 *
 *	File Name: echoserver.cpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Sat 16 Apr 2022 05:09:59 PM CST
 *
 */

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>

int port = 8888;


using namespace std;

int main(int argc, char **argv) {
	struct sockaddr_in serv_addr, clnt_addr;
	int clnt_sock;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket fd
	
	bzero(&serv_addr, sizeof(serv_addr)); // init address struct

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(port);

	if ((bind(sockfd, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr))) == -1) {
		perror("server bind");
		exit(EXIT_FAILURE);
	}

	if ((listen(sockfd, SOMAXCONN)) == -1) {
		perror("server listen");
		exit(EXIT_FAILURE);
	}

	cout << "Server start........\nIP: " << inet_ntoa(serv_addr.sin_addr) << '\n' << "Port: " << port << '\n';
	for (auto i = 0; i < SOMAXCONN; i++) {
		char buf[1024];
		socklen_t addr_sz = sizeof(clnt_addr);
		clnt_sock = accept(sockfd, reinterpret_cast<struct sockaddr*>(&clnt_addr), &addr_sz); // accept a new client socket
		cout << "new client socket is connected...\nConnect client IP: " << inet_ntoa(clnt_addr.sin_addr) << '\n';
		while (read(clnt_sock, buf, 1024) != 0) {
			cout << "rcv: " << buf << '\n';
			write(clnt_sock, buf, strlen(buf));
		}

		close(clnt_sock);
	}
	close(sockfd);



}
