/*
 *
 *	File Name: echoclient.cpp
 *	Author: YangFan
 *	Email: onlyyangfan@protonmail.com
 *	Create Time: Sat 16 Apr 2022 05:10:12 PM CST
 *
 */

/* @#define NETWORK to get network lib   @#define C_LIB to get c lib */
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstring>
#include <arpa/inet.h>


using namespace std;

int main(int argc, char **argv) {
	struct sockaddr_in serv_addr;
	int clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));

	socklen_t addr_sz = sizeof(serv_addr);
	if ((connect(clnt_sock, reinterpret_cast<struct sockaddr*>(&serv_addr), addr_sz)) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);
	}

	cout << "connect to server: " << inet_ntoa(serv_addr.sin_addr) << '\n';

	char buf[1024];
	while (cin>>buf) {
		if (strcmp(buf, "q") == 0){
			cout << "disconnected to server\n";
			close(clnt_sock);
			break;
		}
		write(clnt_sock, buf, strlen(buf));
		bzero(buf, 1024);
		read(clnt_sock, buf, sizeof(buf));
		cout << buf << "\n";
	}
	close(clnt_sock);

}
