/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "main.h"

int main(int argc, char **argv)
{
    char szConfigPath[PATH_MAX];

	pAppPath = GetApplicationPath(argv[0]);
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
