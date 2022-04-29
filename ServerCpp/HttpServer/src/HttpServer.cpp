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
#include <cstring>


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
		cout << "close connect... IP: " << inet_ntoa(this->m_clientAddress.sin_addr) << " port: " << ntohs(this->m_clientAddress.sin_port) << '\n';
	}
}

void HttpServer::acceptRequest() {
	getlineRequest();
	readRequest();
	processRequest();
	this->buff.clear();
}

void HttpServer::getlineRequest() {
	char chr = '\0';
	int readSize = 0;
	while (read(this->m_clientSkt, &chr, 1)) {
		if (chr == '\r') {
			if (read(this->m_clientSkt, &chr, 1)) {
				if (chr == '\n') {
					break;
				}
			}
		} else if (chr == '\n') {
			break;
		} else {
			this->buff.push_back(chr);
		}
	}
}

void HttpServer::readRequest() {
	if (this->m_request.m_isRequestLine == true) {
		string::size_type methodEnd = this->buff.find(" ");
		string method = this->buff.substr(0, methodEnd);
		if (method.compare("GET") == 0) {
			this->m_request.m_requestLine.m_method = Method::GET; // 获得method GET
			string::size_type urlEnd;
			urlEnd = this->buff.find(" ", methodEnd);
			//去除两段的空格
			string url = this->buff.substr(methodEnd+1, urlEnd-1);
			url = url.substr(url.find_first_not_of(" "),url.find_last_of(" "));

			// 提取请求url
			if (url.compare("/") == 0) {
				this->m_request.m_requestLine.m_URL = "./index.html";
			} else {
				this->m_request.m_requestLine.m_URL = url;
			}

			//TODO 提取http协议
			//string::size_type httpProEnd = this->buff.find(" ", urlEnd);
			//string http = this->buff.substr(urlEnd+1, httpProEnd-1);
			//cout << http << endl;

		}
		this->m_request.m_isRequestLine = false;

		// 如果请求文件没有找到返回404
		if (filesystem::is_regular_file(this->m_request.m_requestLine.m_URL)) {
			this->m_response.m_responseLine.m_statusDes = "OK";
			this->m_response.m_responseLine.m_statusCode = StatusDesciption::OK;
		} else {
			this->m_response.m_responseLine.m_statusDes = "Not Found";
			this->m_response.m_responseLine.m_statusCode = StatusDesciption::NotFound;
		}
	}
}

string HttpServer::mergeResponseLine() {
	string data{};
	data += this->m_response.m_responseLine.m_protocol;
	data += " ";
	data += this->m_response.m_responseLine.m_statusCode;
	data += " ";
	data += this->m_response.m_responseLine.m_statusCode;
	data += "\r\n";
	return data;
}



void sendData(string &t_data, int t_clientSkt, string t_URL) {
	//t_data += "Content-Type: text/html; charset=UTF-8\r\n";
	t_data += "\r\n";
	write(t_clientSkt, t_data.c_str(), t_data.size());
	//ifstream fd;
	//fd.open(this->m_request.m_requestLine.m_URL, ios::in);
	//    cout << "Here!\n";
	//char buff[4096];
	//while (fd.getline(buff, 4096)) {
	//    cout << buff << "\n";
	//    write(this->m_clientSkt, buff, 4096); 
	//}
	FILE *fd = fopen(t_URL.c_str(), "r");
	char buf[512];
	fgets(buf, sizeof(buf), fd);

	while (!feof(fd)) {
		write(t_clientSkt, buf, strlen(buf));
	fgets(buf, sizeof(buf), fd);
	}
}

void HttpServer::processRequest() {
	if (this->m_response.m_responseLine.m_statusCode == StatusDesciption::OK) {
		string data = this->mergeResponseLine();
		data += "\r\n";
		thread thd(sendData, ref(data), this->m_clientSkt, this->m_request.m_requestLine.m_URL);

		thd.join();
		close(this->m_clientSkt);
	}
}
