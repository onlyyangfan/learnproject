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
#include "utilies.hpp"

using namespace std;

enum Method {
	GET = 0,
	HEAD,
	POST,
	PUT,
	DELETE,
	TRACE,
	CONNECT,
	OPTIONS
};

//请求头文件的主要布局
// request line \r\n
// request header \r\n
// entity header \r\n
// \r\n
// message body

/* request line部分
request line = methoc SP Request-URI SP HTTP-Version CRLF
request url = "*" | absoluteURI | abs_path | authority
"*" 表示不是请求一个特殊的资源而是请求服务器本身
absoluteURI 一般发送给代理服务器(解析DNS)
authority只用于connect方法
*/

/*request header部分
 *
 *
*/


// 请求头
class RequestLine{
public:
	Method m_method; // 方法
	filesystem::path m_URL; // 请求地址
	string m_protocol; // 协议版本
};

// 请求头部所覆盖的方面太多，这里只是实现accept accept-Encode accept-Language Authorization Host User-Agent
class RequestHeader {
	string m_acceptEncode;
	string m_acceptLanguage;
	string m_host;
	string m_userAgent;
	string m_Authorization;
};

class RequestBody {
	string m_messageBody;
};


class Request {
public:
	RequestLine m_requestLine;
	RequestHeader m_requestHeader;
	RequestBody m_requestBody;
	bool m_isRequestLine = true;
	bool m_isRequestHeader = false;
};

#endif
