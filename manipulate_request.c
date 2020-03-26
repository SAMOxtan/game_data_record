#include "manipulate_request.h"

void match(char* str)
{
    char* pChr1;
    char* pChr2;
    char* pChr3;
    char subjectId[1024] = {0};
    char events[1024] = {0};

    pChr1 = strstr(str, "Id=") + 3;
    pChr2 = strstr(pChr1, "&events=");
    pChr3 = strstr(pChr2, " HTTP");

    strncpy(subjectId, pChr1, pChr2 - pChr1);
    strncpy(events, pChr2 + 8, pChr3 - (pChr2 + 8));
    //printf("%s\n", subjectId);
    //printf("%s\n", events);

    generateStr(subjectId, events);
}

void generateStr(char* subjectId, char* events)
{
    char* timeStr = getTimeString();
    char* line = getLine(72);
    //strcat(subjectId, timeStr);
    //printf("%s\n", subjectId);

    strFomat(events);
    deleteChar(events, Magic_Chr);
    //printf("%s\n",events);

    char* result = strcatAll(6, subjectId, COMMA, timeStr, "\n", line, events);
    printf("%s\n\n",result);
    writeCsv(subjectId, timeStr, result);

    free(timeStr);
    timeStr=NULL;
    free(line);
    line=NULL;
    free(result);
    result=NULL;
}
