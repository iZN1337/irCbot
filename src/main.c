/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "main.h"

int main()
{
    if (!IRC_SetupConfig("config.ini"))
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
    getchar();
    return 0;
}
