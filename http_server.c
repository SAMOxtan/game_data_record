#include "http_server.h"

SOCKET sockSrv;
SOCKET sockConn;

void startServer()
{
    printf("start\n");
    WSADATA wsadata;    //WSADATA数据类型用来存储被WSAStartup函数调用后返回的Windows Sockets数据。
    int port=PORT;      //设置服务器端口号
    char recvBuf[1024]; //接收缓冲区

    //服务器端口号设为9001
    printf("port:%d\n",port);
    WSAStartup(MAKEWORD(2, 2), &wsadata);
    sockSrv = socket(AF_INET, SOCK_STREAM, 0);   //创建用于监听的套接字
    SOCKADDR_IN addrSrv;            //定义一个SOCKADDR_IN类型变量addsrv,表示服务器端的套接字描述符

    addrSrv.sin_family = AF_INET;   //地址族赋值，AF_INET表示IPv4
    addrSrv.sin_port = htons(port); //端口号赋值，1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);   //ip地址赋值，INADDR_ANY表示填入本机ip地址
    bind(sockSrv, (LPSOCKADDR) & addrSrv, sizeof(SOCKADDR_IN));
    listen(sockSrv, 10);
    //printf("服务器端准备完成，开始等待客户机连接请求：\n");

    while(1){
        SOCKADDR_IN addrClient;     //定义一个SOCKADDR_IN类型变量Client,表示客户机端的套接字描述符
        int len = sizeof(SOCKADDR); //取得SOCKADDR_IN结构体的长度
        sockConn = accept(sockSrv, (SOCKADDR * ) & addrClient, &len);//sockConn接收连接请求的套接字描述符
        //printf("与客户机端连接成功，连接的客户机端IP为:%s\n", inet_ntoa(addrClient.sin_addr));//打印客户机ip地址

        memset(recvBuf, 0, sizeof(recvBuf));            //初始化接收服务器端的缓冲区
        recv(sockConn, recvBuf, sizeof(recvBuf), 0);    //接收数据
        match(recvBuf);

        closesocket(sockConn);  // closesocket函数用来关闭一个描述符为sockConn的套接字
    }
    closesocket(sockSrv);
    WSACleanup();   //操作成功返回值为0；否则返回值为SOCKET_ERROR，可以通过调用WSAGetLastError获取错误代码。
}
