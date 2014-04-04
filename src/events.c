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

	printf("%s\n", pLine);

	iSize = explode(&pParts, pLine, ' ');

	if(pParts[0] && pParts[1])
	{
		if (!strcmp(pParts[0], "PING"))
		{
			IRC_SendRaw("PONG %s\r\n", pParts[1]);
		}
		else if(!strcmp(pParts[1], "PRIVMSG"))
		{
			if(pParts[3][1] == ConfigVal(CONFIG_VALUE_PREFIX)[0])
			{
				IRC_ProcessCommand(pParts[2], iSize, &pParts[3]);
			}
		}
		else if (!strcmp(pParts[1], "001"))
		{
			IRC_OnBotConnect();
		}
		else if (!strcmp(pParts[1], "433"))
		{
			IRC_OnNicknameConflict();
		}
	}

	free(pParts);
	return;
}

void IRC_OnNicknameConflict()
{
    IRC_SendRaw("NICK %s_tmp\r\n", ConfigVal(CONFIG_VALUE_NICK));
}

void IRC_OnBotConnect()
{
    IRC_SendRaw("JOIN #no\r\n");
}
