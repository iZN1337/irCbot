/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Add IRC_ReadFile
 */
#include "utils.h"

unsigned int explode(char *szStr, char **ppOut, const char *szDelim)
{
    unsigned int
        i = 0;
    ppOut[0] = strtok(szStr, szDelim);

    while((ppOut[++i] = strtok(NULL, szDelim)) != NULL);

    return i;
}

char* GetApplicationPath(char* szMargv0)
{
	char* addr;
	if((addr = strrchr(szMargv0, '/')) == NULL)
		addr = strrchr(szMargv0, '\\');

	szMargv0[((unsigned int)addr-(unsigned int)szMargv0)+1] = 0;
	return szMargv0;
}

void GetNameFromPath(char* lpOut, const char* szPath, const char* szName)
{
	memset(lpOut, 0, strlen(lpOut));
	strcat(lpOut, szPath);
	strcat(lpOut, szName);
}

signed int GetKeyIndex(const char** ppKeys, const char* szKey)
{
	signed int i = 0;

	do
	{
		if(!strcmp(ppKeys[i], szKey))
			return i;
	}
	while(ppKeys[++i] != NULL);

	return -1;
}

char* IRC_ReadFile(const char* szPath)
{
    FILE
        *pFile;

	char* pContents = NULL;

    if ((pFile = fopen(szPath, "r")) != NULL)
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
