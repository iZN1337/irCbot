/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "commands.h"

/********************** start editing here **********************/

// (INSTANCE iInstance, char* user, char* channel, unsigned int argc, char** args, char* args_raw)

CMD(ping)
{
	IRC_SendRaw(iInstance, "PRIVMSG %s :Pong!", channel);
}

CMD(say)
{
	if(argc)
		IRC_SendRaw(iInstance, "PRIVMSG %s :%s", channel, args_raw);
}

CMD(whoami)
{
	IRC_SendRaw(iInstance, "PRIVMSG %s :You're %s", channel, user);
}

CMD(raw)
{
	if(argc)
		IRC_SendRaw(iInstance, args_raw);
}

CMD(sh)
{
	if(argc)
	{
		char* szChannel, * szArgs;
		szChannel = malloc(64);
		szArgs = malloc(512);
		strcpy(szChannel, channel);
		strcpy(szArgs, args_raw);

		struct system_print_params* sspp = (struct system_print_params*)malloc(sizeof(struct system_print_params));
		sspp->iInstance = iInstance;
		sspp->pChannel = szChannel;
		sspp->pArgs = szArgs;

		THANDLE handle;
		StartThread(&handle, system_print, (void*)sspp);

	}
}

CMD_LIST
{
	CMDDEF(ping),
	CMDDEF(say),
	CMDDEF(whoami),
	CMDDEF(raw),
	CMDDEF(sh)
};


/*********************** stop editing here **********************/

bool IRC_ProcessCommand(INSTANCE iInstance, char* user, char* channel, unsigned int partc, char **command, char* raw)
{
	unsigned int i;
	for(i = 0; i < sizeof(CMDlist)/sizeof(struct CMDstruct);++i)
	{
		if(!strcmp(CMDlist[i].str, &command[0][2]))
		{
			CMDlist[i].func(iInstance, user, channel, partc-4, &command[1], raw);
			return true;
		}
	}
	return false;
}

bool IRC_IsAuthorized(const char *pAddress)
{
    char *pString, szPath[PATH_MAX];
    GetNameFromPath(szPath, pAppPath, "authusers.ini");
    if ((pString = IRC_ReadFile(szPath)) != NULL)
    {
        char *pLine = strtok(pString, "\n");
        do
        {
            if (!strcmp(pLine, pAddress))
                return true;
        }
        while ((pLine = strtok(NULL, "\n")) != NULL);
    }
    return false;
}
