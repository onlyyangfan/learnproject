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



using namespace std;

int main(int argc, char **argv) {
	struct sockaddr_in serv_addr;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); // create socket fd
	
	bzero(&serv_addr, sizeof(serv_addr)); // init address struct

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(8888);

	bind(sockfd, static_cast<sockaddr*>(serv_addr), sizeof(serv_addr));

}
