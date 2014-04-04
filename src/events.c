/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "events.h"

void IRC_ProcessEvents(char *pLine)
{
	char **pParts;
	unsigned int iSize;
	printf("%s\r\n", pLine);
	iSize = explode(&pParts, pLine, ' ');

	if(pParts[0] && pParts[1])
	{
		if (!strcmp(pParts[0], "PING"))
        {
            IRC_SendRaw("PONG %s\r\n", pParts[1]);
            return;
        }
		else if (!strcmp(pParts[1], "JOIN"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "PART"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "KICK"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "QUIT"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "MODE"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "NICK"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "TOPIC"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "NOTICE"))
        {
            return;
        }
        else if (!strcmp(pParts[1], "PRIVMSG"))
        {
            if (pParts[2][0] == '#')
            {
                if (pParts[3][1] == '!')
                {
                    // check if exists blablalbalal
                }
                return;
            }
            else
            {
                return;
            }
        }
        else if (!strcmp(pParts[1], "ERROR"))
        {
            // rip
            return;
        }
        else
        {
            if (!strcmp(pParts[1], "001"))
            {
                IRC_OnBotConnect();
                return;
            }
            else if (!strcmp(pParts[1], "433"))
            {
                IRC_OnNicknameConflict();
                return;
            }
        }
	}
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
