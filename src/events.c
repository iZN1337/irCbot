/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "events.h"

void IRC_ProcessEvents(char* pLine)
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
	}
	else if (!strcmp(pParts[1], "TOPIC"))
	{
		printf("IRC_OnTopic event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "NOTICE"))
	{
		printf("IRC_OnNotice event\r\n");
		continue;
	}
	else if (!strcmp(pParts[1], "PRIVMSG"))
	{
		if (pParts[2][0] == '#')
		{
			printf("CHANNEL MESSAGE!\r\n");

			if (pParts[3][1] == '!')
			{
				printf("COMMAND DETECTED: %s\r\n", strstr(pParts[3], "!"));
				// just for testing
				// no command handler added yet.
				if (!strcasecmp(strstr(pParts[3], "!"), "!say"))
				{
					int i;
					char szParams[128];
					szParams[0] = '\0';
					for (i = 4; i != iSize; ++ i)
					{
						strcat(szParams, pParts[i]);
						strcat(szParams, " ");
					}
					IRC_SendRaw("PRIVMSG %s :%s\r\n", pParts[2], szParams);
					continue;
					/*
					if (pParts[4])
					{
						printf("inside parts 4\r\n");
						int i;
						char *pParams;
						pParams = (char*)malloc(sizeof (pParts[iSize]));
						pParams[0] = '\0';
						for (i = 4; i != iSize; ++ i)
						{
							printf("inside loop\r\n");
							strcat(pParams, pParts[i]);
							strcat(pParams, " ");
						}
						printf("params: %s\r\n", pParams);
						IRC_SendRaw("PRIVMSG %s :%s\r\n", pParts[2], pParams);
						free(pParams);
					}
					else
					{
						IRC_SendRaw("PRIVMSG %s :No params given.\r\n", pParts[2]);
					}

				}
			}
		}
		else
		{
			printf("PRIVATE MESSAGE!\r\n");
			continue;
		}
	}
	else if (!strcmp(pParts[1], "ERROR"))
	{
		printf("IRC_OnError event\r\n");
		continue;
	}
	else
	{
		printf("=> %s\r\n", pParts[1]);
		if (!strcmp(pParts[1], "001"))
		{
			IRC_SendRaw("JOIN #no\r\n");
			continue;
		}
		else if (!strcmp(pParts[1], "433"))
		{
			// nick name conflict
			continue;
		}
	}*/

	if(pParts)
		free(pParts);
}
