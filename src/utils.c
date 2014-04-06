/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "utils.h"

unsigned int explode(char ***arr_ptr, char *str, const char delimiter)
{
	char *src = str, *end, *dst;
	char **arr;
	unsigned int size = 1, i;

	while ((end = strchr(src, delimiter)) != NULL)
	{
	  ++size;
	  src = end + 1;
	}

	arr = malloc(size * sizeof(char *) + (strlen(str) + 1) * sizeof(char));

	src = str;
	dst = (char *) arr + size * sizeof(char *);
	for (i = 0; i < size; ++i)
	{
		if ((end = strchr(src, delimiter)) == NULL)
		end = src + strlen(src);
		arr[i] = dst;
		strncpy(dst, src, end - src);
		dst[end - src] = '\0';
		dst += end - src + 1;
		src = end + 1;
	}
	*arr_ptr = arr;

	return size;
}

char* GetApplicationPath(char *szMargv0)
{
	char *pAddr;
	if((pAddr = strrchr(szMargv0, '/')) == NULL) // get a pointer to the last instance of a character which is not a windows system directory delimiter
		pAddr = strrchr(szMargv0, '\\'); // get a pointer to the last instance of a character which is a windows system directory delimiter

	szMargv0[((unsigned int)pAddr - (unsigned int)szMargv0) + 1] = 0; // calculate offsets, set the appropriate char to 0 to remove filename
	return szMargv0; // return a pointer to the filename
}

void GetNameFromPath(char *lpOut, const char *szPath, const char *szName)
{
	memset(lpOut, 0, strlen(lpOut)); // set memory
	strcat(lpOut, szPath); // append path to empty string
	strcat(lpOut, szName); // append file name to path
}

signed int GetKeyIndex(const char** ppKeys, const char* szKey)
{
	signed int i = 0;
	do
	{
		if(!strcmp(ppKeys[i], szKey)) // if the keys match, return the index
			return i;
	}
	while(ppKeys[++i] != NULL); // while pointer is valid
	return -1; // no matching keys found
}

char* IRC_ReadFile(const char *szPath)
{
    FILE *pFile;
	char *pContents = NULL;

    if ((pFile = fopen(szPath, "r")) != NULL) // open file with read permissions
    {
    	if (fseek(pFile, 0, SEEK_END) != 0) // go to end of file
			return pContents;

		long lFileSize = ftell(pFile); // get current position (set to end of file above), used to get the file length
		if(fseek(pFile, 0, SEEK_SET) != 0) // set back to the beginning
			return pContents;

		pContents = malloc(lFileSize+1); // allocate memory to store the contents of the file
		fread(pContents, 1, lFileSize, pFile); // read the file and store contents into memory

	}
	fclose(pFile);
	return pContents; // return a pointer to the file contents
}

char *trim(char *szString)
{
	unsigned int i = 0, j = strlen(szString);

	while(isspace(szString[i++]));
	while(isspace(szString[--j]));

	szString[j+1] = 0;
	return &szString[i-1];
}

char* replace_first(char* szString, const char cChr, const char cReplacement)
{
	char* pChar = strchr(szString, cChr);
	if(pChar == NULL)
		return NULL;

	*pChar = cReplacement;
	return pChar;
}

char* IRC_GetParameterAt(const char* szLine, unsigned int iNum)
{
	int i = 0;
	char* pParam;

	pParam = strchr(szLine, ' ');
	while(pParam && ++i < iNum)
		pParam = strchr(pParam+1, ' ');

	return pParam+1;
}

THREAD_CALLBACK system_print(void* lpParam)
{
		FILE *pOutput;
		char szLine[476];

		struct system_print_params* params = (struct system_print_params*)lpParam;

		pOutput = popen(params->pArgs, "r");

		while(fgets(szLine, 1024, pOutput) != NULL)
			IRC_SendRaw(params->iInstance, "PRIVMSG %s :%s", params->pChannel, szLine);

		pclose(pOutput);
		free(params->pArgs);
		free(params->pChannel);
		free(lpParam);
		return 0;
}
