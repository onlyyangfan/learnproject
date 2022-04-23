/*
 *
 *	File Name: Response.hpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Sat 23 Apr 2022 10:00:51 AM CST
 *
 */

#pragma once

#include "utilies.hpp"

/* resond布局
 * status-line \r\n
 * respond header \r\n
 * \r\n
 * message body
 */

// status line = Http protocol SP Status-Code SP Reason-Phrase CRLF

// status code 
// •1xx: Informational - Request received, continuing process
//•2xx: Success - The action was successfully received, understood, and accepted
//•3xx: Redirection - Further action must be taken in order to complete the request
//•4xx: Client Error - The request contains bad syntax or cannot be fulfilled
//• 5xx: Server Error - The server failed to fulfill an apparently valid request
//


enum StatusDesciption {
	OK = 200,
	Created,
	Accepted,
	NoAuthorInfo,
	NoContent,
	BadRequest = 400,
	Unauthor,
	Forbidden = 403,
	NotFound,
	MethodNotAllowed,
	NotAccept,
	RequestTimeOut=408,
	InterServerErr = 500,
	NotImplement,
	BadGateway,
	ServiceUnavailable,
};

class ResponseLine{
public:
	string m_protocol;
	int m_statusCode;
	StatusDesciption m_statusDes;
};

class ResponseHeader {
public:
	string m_server;
	string m_location;
	struct tm m_age;
};

class ResponseData {
	string m_meessageBody;
};
