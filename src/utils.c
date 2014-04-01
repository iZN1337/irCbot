/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "utils.h"

unsigned int explode(char *pStr, char **pOut, const char *pDelim)
{
    unsigned int
        i = 0;
    pOut[0] = strtok(pStr, pDelim);

    while((pOut[++i] = strtok(NULL, pDelim)) != NULL);

    return i;
}

void GetNameFromPath(char* out, const char* path, const char* name)
{
	memset(out, 0, strlen(out));
	strcat(out, path);
	strcat(out, name);
}
