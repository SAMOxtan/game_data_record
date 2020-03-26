#include <pthread.h>
#include "manage_process.h"
#include "http_server.h"

int main(int argc, const char *argv[])
{
    /*
    HWND hwnd;
    hwnd=FindWindow("ConsoleWindowClass",NULL); //处理顶级窗口的类名和窗口名称匹配指定的字符串,不搜索子窗口。
    if(hwnd)
    {
        ShowWindow(hwnd,SW_HIDE);               //设置指定窗口的显示状态
    }
    */
    try{
        if(!isStartProcess(argv[0]) && !isUsedPort(PORT)){
            PROCESS_INFORMATION* pi = create();
            pthread_t gameThread;
            pthread_create(&gameThread, NULL, waitProcess, pi);

            startServer();

            pthread_join(gameThread,NULL);
        }
        else
            throw;
    }catch{
        //system("pause");

        //closesocket(sockSrv);
        return -1;
    }
    return 0;
}
