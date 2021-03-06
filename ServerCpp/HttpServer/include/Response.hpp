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
	std::string m_protocol{"Http/1.0"};
	StatusDesciption m_statusCode;
	std::string m_statusDes;
};

class ResponseHeader {
public:
	std::string m_server;
	std::string m_location;
	struct tm m_age;
};

class ResponseData {
	std::string m_meessageBody;
};

class Response {
public:
	ResponseLine m_responseLine;
	ResponseHeader m_responseHeader;
	ResponseData m_responseData;
};
