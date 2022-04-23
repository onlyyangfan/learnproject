/*
 *
 *	File Name: Url.hpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Sat 23 Apr 2022 08:06:44 AM CST
 *
 */

#pragma once
#include <string>

using namespace std;

//http_URL = "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]
//If the port is empty or not given, port 80 is assumed. The semantics
//are that the identified resource is located at the server listening
//for TCP connections on that port of that host, and the Request-URI
//for the resource is abs_path (section 5.1.2). The use of IP addresses
//in URLs SHOULD be avoided whenever possible (see RFC 1900 [24]). If
//the abs_path is not present in the URL, it MUST be given as "/" when
//used as a Request-URI for a resource (section 5.1.2). If a proxy
//receives a host name which is not a fully qualified domain name, it
//MAY add its domain to the host name it received. If a proxy receives
//a fully qualified domain name, the proxy MUST NOT change the host
//name.
enum HttpProtocl{
	http,
	https
};

class Url {
public:
	Url() {
		m_ip = 80;
		m_absPath = "\\";
	}
	Url(HttpProtocl ptl, string ip, string abspath) : m_protocl(ptl), m_ip(ip), m_absPath(abspath){}
private:
	HttpProtocl m_protocl;	
	string m_ip;
	string m_absPath;
	
};
