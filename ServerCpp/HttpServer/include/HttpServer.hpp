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
#include "Response.hpp"
#include <cstdio>

class HttpServer {
public:
	void serverInit();
	void connect(); 
	void acceptRequest();
	void getlineRequest();
	void readRequest();
	void processRequest();
	//void sendData(string &t_data);
	std::string mergeResponseLine();

	int getClientSkt() {
		return this->m_clientSkt;
	}
	
	std::string getURL() {
   		return this->m_request.m_requestLine.m_URL.c_str();
   }		

   friend void sendData(std::string &, HttpServer *http);
private:
	int m_serverSkt = 0;
	int m_clientSkt = 0;
	int m_port = 8888;
	struct sockaddr_in m_serverAddress;
	struct sockaddr_in m_clientAddress;
	std::string buff{};
	Request m_request; //接受的请求
	Response m_response; // 回复
						 //
};


#endif
