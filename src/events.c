/**
* @project: irCbot - An Internet Relay Chat bot written in C
* @file: events.c
* @author: Djole, King_Hual &lt;djolel@net.dut.edu.vn&gt;, &lt;king_hell@abv.bg&gt;
* @last update: N/A
*/

#include "events.h"

void IRC_ProcessEvents(char *pLine)
{
    char **pParts;
    unsigned int iSize;
    printf("%s\r\n", pLine);
    iSize = explode(&pParts, pLine, ' ');

    if (pParts[0] && pParts[1])
    {
        if (!strcmp(pParts[0], "PING"))
        {
            IRC_SendRaw("PONG %s\r\n", pParts[1]);
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "JOIN"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "PART"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "KICK"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "QUIT"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "MODE"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "NICK"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "TOPIC"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "NOTICE"))
        {
            goto iExitLoc;
        }
        else if (!strcmp(pParts[1], "PRIVMSG"))
        {// +%@#
            switch ()
            {
                case '#':
                case '+':
                case '%':
                case '@':
                {
                    if (pParts[3][1] == ConfigVal(CONFIG_VALUE_PREFIX)[0])
                    {
                        IRC_ProcessCommand(pParts[2], iSize, &pParts[3]);
                    }
                    goto iExitLoc;
                }
            }
            else
            {
                goto iExitLoc;
            }
        }
        else if (!strcmp(pParts[1], "ERROR"))
        {
            // rip
            goto iExitLoc;
        }
        else
        {
            if (!strcmp(pParts[1], "001"))
            {
                IRC_OnBotConnect();
                goto iExitLoc;
            }
            else if (!strcmp(pParts[1], "433"))
            {
                IRC_OnNicknameConflict();
                goto iExitLoc;
            }
        }
    }
    iExitLoc:
    free(pParts);
}

void IRC_OnNicknameConflict()
{
    IRC_SendRaw("NICK %s_tmp\r\n", ConfigVal(CONFIG_VALUE_NICK));
}

void IRC_OnBotConnect()
{
    IRC_SendRaw("JOIN #no\r\n");
}
