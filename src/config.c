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
	"cmdprefix",	// CONFIG_VALUE_CMDDELIM
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
			char *pValue = NULL;

			char* comment = replace_first(pLine, ';', 0); // remove comments if there are any, return pointer to the replaced char

			if(comment)
			{
				comment = trim(++comment); // get the comments just because we can
			}

			pValue = memchr(pLine, '=', strlen(pLine)); // get '=' position

			if(pValue != NULL) // '=' is found
			{
				*pValue++ = 0; // set '=' to '\0', this splits the line into 2, and pointer is set to the char after

				char* pKey = trim(pLine); // trim space from key
				pValue = trim(pValue); // trim space from value

				printf("%s %s.\n", pKey, pValue);

				signed int iIdx = GetKeyIndex(ppConfigKeys, pKey); // get the index of the key (to be stored in the appropriate index in ppConfig)

				if(iIdx != -1) // if key is valid
					ppConfig[iIdx] = pValue; // store value in global configuration values array
			}
		}
		return 1; // success
	}
    return 0; // error
}
