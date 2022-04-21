/*
 *
 *	File Name: Request.hpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Thu 21 Apr 2022 02:27:24 PM CST
 *
 */

// 请求头文件

#ifndef REQUESTHEAD
#define REQUESTHEAD
#include <string>

using namespace std;

enum class Method {
	GET = 0,
	HEAD,
	POST,
	PUT,
	DELETE,
	TRACE,
	CONNECT,
	OPTIONS
};

// 请求头
class RequestHeader {
public:
	Method m_method; // 方法
	string m_URL; // 请求地址
	string m_protocol; // 协议版本

};

#endif
