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
<<<<<<< HEAD
    unsigned int iSize;

	printf("%s\n", pLine);

=======
	unsigned int iSize;
	printf("%s\r\n", pLine);
>>>>>>> f5c85d8a44af407c3c13bae63b7838a654a9129f
	iSize = explode(&pParts, pLine, ' ');

	if(pParts[0] && pParts[1])
	{
		if (!strcmp(pParts[0], "PING"))
<<<<<<< HEAD
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
			IRC_SendRaw("JOIN #no\r\n");
		}
	}

	/*else if (!strcmp(pParts[1], "JOIN"))
	{
		printf("IRC_OnJoin event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "PART"))
	{
		printf("IRC_OnPart event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "KICK"))
	{
		printf("IRC_OnKick event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "QUIT"))
	{
		printf("IRC_OnQuit event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "MODE"))
	{
		printf("IRC_OnMode event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "NICK"))
	{
		printf("IRC_OnNick event\r\n");
		continue;
=======
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
>>>>>>> f5c85d8a44af407c3c13bae63b7838a654a9129f
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
