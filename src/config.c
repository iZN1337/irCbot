/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "config.h"

const static char *ppConfigKeys[INI_MAX_KEYS] = // a private constant array that stores keys
{
	"server",		// CONFIG_VALUE_SERVER
	"port",			// CONFIG_VALUE_PORT
	"ssl",			// CONFIG_VALUE_SSL
	"nickname",		// CONFIG_VALUE_NICK
	"username",		// CONFIG_VALUE_USER
	"realname",		// CONFIG_VALUE_REAL
	"cmddelimiter",	// CONFIG_VALUE_CMDDELIM
	"channels",		// CONFIG_VALUE_CHANNELS
	"perform"		// CONFIG_VALUE_PERFORM
};

char *ppConfig[INI_MAX_KEYS]; // initializing the global pointer array

int IRC_SetupConfig(const char *pLocation)
{
	char* pString = IRC_ReadFile(pLocation); // get a pointer to the file contents as a string

	if(pString != NULL) // file was read successfully
	{
		char *pLine = strtok(pString, "\n"); // split line by line
		while((pLine = strtok(NULL, "\n")) != NULL) // loop through the lines
		{
			if(pLine[0] != ';') // not a comment
			{
				char *pKey = pLine, *pValue = NULL;

				pValue = memchr(pLine, '=', strlen(pLine)); // get '=' position
				if(pValue != NULL) // = is found
				{
					*pValue ++ = 0; // set = to \0, this splits the line into 2, and pointer is set to the char after
					signed int iIdx = GetKeyIndex(ppConfigKeys, pKey); // get the index of the key (to be stored in the appropriate index in ppConfig)

					if(iIdx != -1) // if key is valid
						ppConfig[iIdx] = pValue; // store value in global configuration values array
				}
			}
		}
		return 1; // success
	}
    return 0; // error
}
