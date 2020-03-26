#include "manipulate_string.h"

char* strcatAll(int dwArgNum,char* str, ...)
{
    va_list pArgs = NULL;
    va_start(pArgs, str);
    int length = strlen(str);
    for(int i = 1; i < dwArgNum; i++)
        length += strlen(va_arg(pArgs, char*));
    va_end(pArgs);

    char* result=(char*)malloc(length+1);
    if(result == NULL){
        printf("strcatAll Malloc Error");
        throw;
    }
    memcpy(result, str, strlen(str)+1);

    va_start(pArgs, str);
    for(int i = 1; i < dwArgNum; i++)
        strcat(result, va_arg(pArgs, char*));
    va_end(pArgs);

    return result;
}

void strFomat(char *str)
{
    char* pCom1 = str +1;
    char* pCom2 = NULL;
    char* pCom3 = NULL;
    char* pRound = NULL;

    while(1){
        pCom1 = strstr(pCom1, COMMA) + 1;
        pCom2 = strstr(pCom1, COMMA) + 1;

        pRound = strstr(pCom2, "round");

        if(pRound == pCom2 && pCom3){
            *pCom3 = '\n';
            int frame = atoi(pCom1);
            if(frame == 209){
                pCom1[0] = '1';
                pCom1[1] = pCom1[2] = Magic_Chr;
            }
        }
        pCom3 = strstr(pCom2, COMMA);
        if(!pCom3)    break;
        pCom1 = pCom3 + 1;
    }
}

void deleteChar(char str[], char symbol)
{
	int i, j;
	for(i = j = 0; str[i]; i++){
		if(str[i] != symbol){
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}

int getCharNum(char* str, char symbol)
{
    int num = 0;

    char* pChr = str;
    //printf("pchr:%s\n",str);
    while(pChr = strchr(pChr, symbol)){
        num++;
        pChr++;
    }
    return num;
}

char* getTimeString()
{
    char* timeStr = (char*)malloc(16);
    if(timeStr == NULL){
        printf("getTimeString Malloc Error");
        throw;
    }
    time_t times = time(NULL);
    struct tm* utcTime = gmtime(&times);
    sprintf(timeStr, "%04d%02d%02dT%02d%02d%02d",
            utcTime  -> tm_year + 1900,
            utcTime  -> tm_mon + 1,
            utcTime  -> tm_mday,
            (utcTime -> tm_hour + 8) % 24,
            utcTime  -> tm_min,
            utcTime  -> tm_sec
            );
    timeStr[15] = '\0';
    return timeStr;
}

char* getLine(int num)
{
    char* line = (char*)malloc(num + 2);
    if(line == NULL){
        printf("getLine Malloc Error");
        throw;
    }
    memset(line, '-', num);
    line[num] = '\n';
    line[num + 1] = 0;
    return line;
}

void writeCsv(char* filename, char* timeStr, char* str)
{
    FILE *fp = NULL;
    char* filepath=strcatAll(5, PATH, filename, COMMA, timeStr, File_Format);

    //strcpy(filepath, PATH);
    //strcat(filepath, filename);
    //strcat(filepath, File_Format);
    printf("%s\n\n", filepath);
    fp = fopen(filepath, "w+");
    if(fp == NULL){
        printf("Save Csv Error");
        //throw;
    }
    //printf("write:%s\n",str);
    fprintf(fp, str);
    free(filepath);
    fclose(fp);
}
