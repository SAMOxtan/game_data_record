#include "manage_process.h"
#include "http_server.h"
PROCESS_INFORMATION* create()
{
    TCHAR* commandLine = TEXT(GAME);
    STARTUPINFO si = {sizeof(si)};

    PROCESS_INFORMATION* pi = (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION));
    int bRet = CreateProcess(
        NULL,
        commandLine,
        NULL,
        NULL,
        FALSE,
        CREATE_NO_WINDOW,
        NULL,
        NULL,
        &si,
        pi);
    int error = GetLastError();
    if (!bRet)
    {
        printf("Open Game Error");
        throw;
        //printf("进程ID：%d\n", pi->dwProcessId);
        //printf("线程ID：%d\n", pi->dwThreadId);
    }
    //printf("%d\n", bRet);
    return pi;
}

void* waitProcess(PROCESS_INFORMATION* pi)
{
    WaitForSingleObject(pi->hProcess, INFINITE);
    //printf("over!\n");
    closesocket(sockConn);
    closesocket(sockSrv);
    WSACleanup();
    //system("pause");
    free(pi);
    exit(0);
}

void _System(const char* cmd, char* pRetMsg, int msg_len)
{
	FILE* fp;
	char* p = NULL;
	int res = -1;
	if (cmd == NULL || pRetMsg == NULL || msg_len < 0){
		printf("Param Error");
		throw;
	}
	if ((fp = _popen(cmd, "r")) == NULL){
		printf("Popen Error");
		throw;
	}
	else{
		memset(pRetMsg, 0, msg_len);
		//get lastest result
		fgets(pRetMsg, msg_len, fp);
		if ((res = _pclose(fp)) == -1){
			printf("Close Popen Error");
			throw;
		}
		pRetMsg[strlen(pRetMsg)] = 0; //防止长度超过128,进行截断
	}
}

char* getProcessName(char* filepath)
{
    char* fileName = strrchr(filepath, '\\') + 1;
    //printf("%s\n", fileName); // Here's FileName.
    return fileName;
}

char* execute(char* command, char* avg)
{
    char* cmd = strcatAll(2, command, avg);
    //printf("cmd:%s\n", cmd);
    int size = 128;
	char* result = (char*)malloc(size);
	if(result == NULL){
        printf("execute Malloc Error");
        throw;
    }
	memset(result, 0, size);
	_System(cmd, result, size);
	//printf("%s\nlength = %d \n", result, strlen(result));
	//printf("result:%s\n", result);
	return result;
}

int isFail(char* result)
{
    char* fail = strrchr(result, '"');
    if(fail)
        return 1;
    else
        return 0;
}

int isUsedPort(int port)
{
    int ret = 0;
    char portChr[16] = {0};
    itoa(port, portChr, 10);
    char* findResult = execute(FINDNETS, portChr);
    //printf("findResult:%s\nnum:%d\nlen:%d\n",findResult, getCharNum(findResult,'\n'),strlen(findResult));
    if(*findResult){
        char* pid = strrchr(findResult, ' ') + 1;

        if(atoi(pid) != 0){//NOT TIME_WAIT
            ret = 1;
            printf("%d port is already in use!\n", port);
        }
        /*
        char* pid = strrchr(findResult, ' ') + 1;
        char* killResult = execute(KILLPID, pid);
        return isFail(killResult);
        */
    }
    free(findResult);
    return ret;
}

int isStartProcess(char* filepath)
{
    int ret = 0;
    char* fileName = getProcessName(filepath);
    char* findResult = execute(FINDTASK, fileName);
    //printf("findResult:%s\n",findResult);
    if(*findResult && getCharNum(findResult,'\n') > 1){
        char* killResult = execute(KILLNAME, fileName);
        ret = isFail(killResult);
    }
    free(findResult);
    return ret;
    /*
    if(!*findResult || getCharNum(findResult,'\n') <= 1){
        free(findResult);
        return 0;
    }
    else{
        free(findResult);
        char* killResult = execute(KILLNAME, fileName);
        return isFail(killResult);
    }
    */
}
