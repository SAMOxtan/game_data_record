#ifndef MANAGEPROCESS_H_INCLUDED
#define MANAGEPROCESS_H_INCLUDED

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "manipulate_string.h"

#define FINDTASK "tasklist |findstr "

#define FINDNETS "netstat -aon|findstr "

#define KILLPID "taskkill /F /T /PID "

#define KILLNAME "taskkill /F /T /IM "

PROCESS_INFORMATION* create();

void* waitProcess(PROCESS_INFORMATION* pi);

void _System(const char * cmd, char *pRetMsg, int msg_len);

char* getProcessName(char* filepath);

char* execute(char* command, char* avg);

int isFail(char* result);

int isUsedPort(int port);

int isStartProcess(char* filepath);
#endif // MANAGEPROCESS_H_INCLUDED
