/*
 *
 *	File Name: HttpServer.cpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Thu 21 Apr 2022 03:20:37 PM CST
 *
 */

/* @#define NETWORK to get network lib   @#define C_LIB to get c lib */

#include "../include/HttpServer.hpp"


void HttpServer::serverInit() {
	this->m_serverSkt = socket(AF_INET, SOCK_STREAM, 0);

	//setsockopt(this->m_serverSkt, SOL_SOCKET, SO_REUSEADDR, nullptr, 0);
	this->m_serverAddress.sin_family = AF_INET;
	this->m_serverAddress.sin_port = htons(this->m_port);
	this->m_serverAddress.sin_addr.s_addr = inet_addr("192.168.2.218");  
	int option = 1;
	setsockopt(this->m_serverSkt, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<void*>(&option), sizeof(option));


	if ((bind(this->m_serverSkt, reinterpret_cast<struct sockaddr*>(&this->m_serverAddress), sizeof(this->m_serverAddress))) == -1) {
		perror("bind");
		exit(-1);
	}
	if ((listen(this->m_serverSkt, socketLength)) < 0) {
		perror("listen");
		exit(-1);
	}

	cout << "Host server start...\n" << "IP: " <<  inet_ntoa(this->m_serverAddress.sin_addr) << "\tport: " << this->m_port << "\n";
}

void HttpServer::connect() {
	cout << "Wait client to connect...\n";
	while (true) {
		socklen_t clientAddressLen = sizeof(this->m_clientAddress);
		this->m_clientSkt = accept(this->m_serverSkt, reinterpret_cast<struct sockaddr*>(&(this->m_clientAddress)), &clientAddressLen);
		if (this->m_clientSkt < 0) {
			cout << "error\n";
		}
		cout << "new connect... IP: " << inet_ntoa(this->m_clientAddress.sin_addr) << " port: " << ntohs(this->m_clientAddress.sin_port) << '\n';
		this->acceptRequest();
		close(this->m_clientSkt);
		cout << "close connect... IP: " << inet_ntoa(this->m_clientAddress.sin_addr) << " port: " << ntohs(this->m_clientAddress.sin_port) << '\n';
	}
}

void HttpServer::acceptRequest() {
}

void HttpServer::getlineRequest() {
	char chr = '\0';
	int readSize = 0;
	while (chr != '\n') {
		if (read(this->m_clientSkt, &chr, 1) > 0 ) {
			if (chr != '\r') {
				if (read(this->m_clientSkt, &chr, 1) && chr == '\n') {
					
				}
					
			}
		} else {
			chr = '\n';
		}
	}
}
