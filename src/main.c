/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Add proper application path string
 */
#include "main.h"

int main(int argc, char **argv)
{
	char
	    *pAddr, szConfigPath[PATH_MAX];
		
	if ((pAddr = strrchr(argv[0], '/')) == NULL)
		pAddr = strrchr(argv[0], '\\');

	argv[0][((unsigned int)pAddr - (unsigned int)argv[0]) + 1] = 0;
	pAppPath = argv[0];

	GetNameFromPath(szConfigPath, pAppPath, "config.ini");


    if (!IRC_SetupConfig(szConfigPath))
    {
        printf("Fatal error: Failed to load config!\n");
        goto iExitLoc;
    }

    if (!IRC_AttemptConnection("94.242.253.75", 6667))
    {
        printf("Fatal error: Failed to connect on IRC network!\n");
        goto iExitLoc;
    }

    iExitLoc:
    return 0;
}
