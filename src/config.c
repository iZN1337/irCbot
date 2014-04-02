/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */
#include "config.h"

const static char *ppConfigKeys[INI_MAX_KEYS] =
{
	"server",
	"port",
	"ssl",
	"nickname",
	"username",
	"realname",
	"cmddelimiter",
	"channels",
	"perform"
};

char *ppConfig[INI_MAX_KEYS];

int IRC_SetupConfig(const char *pLocation)
{
	char* pString = IRC_ReadFile(pLocation);

	if(pString != NULL)
	{
		char *pLine = strtok(pString, "\n");
		while((pLine = strtok(NULL, "\n")) != NULL)
		{
			if(pLine[0] != ';')
			{
				char *pKey = pLine, *pValue = NULL;

				pValue = memchr(pLine, '=', strlen(pLine));
				if(pValue != NULL)
				{
					*pValue ++ = 0;
					signed int iIdx = GetKeyIndex(ppConfigKeys, pKey);

					if(iIdx != -1)
						ppConfig[iIdx] = pValue;
				}
			}
		}
		return 1;
	}
    return 0;
}
