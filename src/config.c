/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "config.h"
int IRC_SetupConfig(const char *pLocation)
{
    FILE
        *pFile;
    char
        szBuffer[1024];
    if ((pFile = fopen(pLocation, "r")) != NULL)
    {
        while (fgets(szBuffer, sizeof (szBuffer), pFile) != NULL)
        {
            if (szBuffer[0] != ';' && szBuffer[0] != '\n') /* Skipping comments and new lines */
            {
                // finish
            }
        }
        return 1;
    }
    return 0;
}
