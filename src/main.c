/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Add proper application path string
 */
#include "main.h"

char* szAppPath;

int main(int argc, char **argv)
{
	// get application startup path

	char* addr;
	if((addr = strrchr(argv[0], '/')) == NULL)
		addr = strrchr(argv[0], '\\');

	argv[0][((unsigned int)addr-(unsigned int)argv[0])+1] = 0;
	szAppPath = argv[0];

	char szConfigPath[PATH_MAX];
	GetNameFromPath(szConfigPath, szAppPath, "config.ini");


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
