/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Add IRC_ReadFile
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

char* IRC_ReadFile(const char* pPath)
{
    FILE
        *pFile;

	char* pContents = NULL;

    if ((pFile = fopen(pPath, "r")) != NULL)
    {
    	if (fseek(pFile, 0, SEEK_END) != 0)
			return pContents;

		long lFileSize = ftell(pFile);
		if(fseek(pFile, 0, SEEK_SET) != 0)
			return pContents;

		pContents = malloc(lFileSize+1);
		fread(pContents, 1, lFileSize, pFile);

	}
	return pContents;
}
