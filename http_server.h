#ifndef HTTP_SERVER_H_INCLUDED
#define HTTP_SERVER_H_INCLUDED

#include <WinSock2.h>

#include "manipulate_request.h"

#define PORT 9001

#pragma comment(lib, "wevents_32.lib")

void startServer();

extern SOCKET sockSrv;

extern SOCKET sockConn;

#endif // HTTP_SERVER_H_INCLUDED
