/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "main.h"

int main(int argc, char **argv) // entry point
{
    char szConfigPath[PATH_MAX]; // initialize a char array

	pAppPath = GetApplicationPath(argv[0]); // get the application path, argv[0] always stores application path
	GetNameFromPath(szConfigPath, pAppPath, "config.ini"); // append "config.ini" to the application path

    if (!IRC_SetupConfig(szConfigPath)) // load configuration from file
    {
        printf("Fatal error: Failed to load config!\n");
        goto iExitLoc;
    }

    if (!IRC_AttemptConnection("94.242.253.75", 6667)) // connect to IP
    {
        printf("Fatal error: Failed to connect on IRC network!\n");
        goto iExitLoc;
    }

    iExitLoc:
    return 0;
}
