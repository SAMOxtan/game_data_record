#ifndef MANIPULATE_STRING_H_INCLUDED
#define MANIPULATE_STRING_H_INCLUDED

#include <stdio.h>

#include<string.h>

#include <stdlib.h>

#include <time.h>

#include <stdarg.h>

#include <Windows.h>

#include "exception.h"

#define Magic_Chr 8

#define File_Format ".csv"

#define PATH "./data/"

#define GAME "./tsg.exe"

#define COMMA ","

char* strcatAll(int dwArgNum,char* str, ...);

void strFomat(char *str);

void deleteChar(char str[], char symbol);

int getCharNum(char* str, char symbol);

char* getTimeString();

char* getLine(int num);

void writeCsv(char* filename, char* timeStr, char* str);

#endif // MANIPULATE_STRING_H_INCLUDED
