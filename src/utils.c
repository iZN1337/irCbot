/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "utils.h"
/*
unsigned int explode(char *szStr, char **ppOut, const char *szDelim, const size_t limit)
{
    unsigned int
        i = 0;

    ppOut[0] = strtok(szStr, szDelim); // split by delim
    while(i != limit-1 && (ppOut[++i] = strtok(NULL, szDelim)) != NULL ); // set ppOut to point to the appropriate split string
	ppOut[i+1] = ppOut[i]+strlen(ppOut[i])+1;

    return i; // return number of strings the string was split into
}*/

int explode(char ***arr_ptr, char *str, char delimiter)
{
  char *src = str, *end, *dst;
  char **arr;
  int size = 1, i;

  // Find number of strings
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
