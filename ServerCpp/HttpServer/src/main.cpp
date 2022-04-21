/*
 *
 *	File Name: main.cpp
 *	Author: YangFan
 *	Email: NonShip@protonmail.com
 *	Create Time: Thu 21 Apr 2022 06:39:14 PM CST
 *
 */

/* @#define NETWORK to get network lib   @#define C_LIB to get c lib */
#include "../include/HttpServer.hpp"

using namespace std;

int main(int argc, char **argv) {
	HttpServer httpserv;
	httpserv.serverInit();
	httpserv.connect();
}
