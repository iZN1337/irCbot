/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "commands.h"

/********************** start editing here **********************/

// (char* user, char* channel, unsigned int argc, char** args, char* args_raw)

CMD(ping)
{
	IRC_SendRaw("PRIVMSG %s :Pong!", channel);
}

CMD(say)
{
	if(argc)
		IRC_SendRaw("PRIVMSG %s :%s", channel, args_raw);
}

CMD(whoami)
{
	IRC_SendRaw("PRIVMSG %s :You're %s", channel, user);
}

CMD_LIST
{
	CMDDEF(ping),
	CMDDEF(say),
	CMDDEF(whoami)
};


/*********************** stop editing here **********************/

bool IRC_ProcessCommand(char* user, char* channel, unsigned int partc, char **command, char* raw)
{
	unsigned int i;
	for(i = 0; i < sizeof(CMDlist)/sizeof(struct CMDstruct);++i)
	{
		if(!strcmp(CMDlist[i].str, &command[0][2]))
		{
			CMDlist[i].func(user, channel, partc-4, &command[1], raw);
			return true;
		}
	}
	return false;
}
