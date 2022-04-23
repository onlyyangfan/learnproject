/*
 *
 *	File Name: HttpServer.hpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Thu 21 Apr 2022 03:10:47 PM CST
 *
 */

// 服务器的主体

#ifndef HTTPSERVER
#define HTTPSERVER

#include "utilies.hpp"
#include "Request.hpp"
#include <cstdio>

class HttpServer {
public:
	void serverInit();
	void connect(); 
	void acceptRequest();
	void getlineRequest();
private:
	int m_serverSkt = 0;
	int m_clientSkt = 0;
	int m_port = 8888;
	struct sockaddr_in m_serverAddress;
	struct sockaddr_in m_clientAddress;
	string buff{};
};


#endif
