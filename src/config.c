/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Update configuration parser
 */
#include "config.h"

int IRC_SetupConfig(const char *pLocation)
{
	char* pString = IRC_ReadFile(pLocation);
	if(pString != NULL)
	{
		char* pLine = strtok(pString, "\n");
		while((pLine = strtok(NULL, "\n")) != NULL)
		{
			if(pLine[0] != ';' && pLine[0] != '\n')
			{
				char* key = pLine,* pValue = NULL;
				pValue = memchr(pLine, '=', strlen(pLine));
				if(pValue != NULL)
					*pValue++ = 0;

				return 1;
			}
		}
	}

	/** commented out as pointers will be stored globally **/
	//free(pString);
    return 0;
}
