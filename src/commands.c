/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "commands.h"

/********************** start editing here **********************/

void CMD_Ping(char* channel, unsigned int argc, char** args)
{
	IRC_SendRaw("PRIVMSG %s :Pong!\r\n", channel);
}

CMD_LIST
{
	{ CMD_S("ping"), CMD_F(CMD_Ping) } // when a user types !ping, call CMD_Ping
};

/*********************** stop editing here **********************/

static void (*cmd)(char*, unsigned int, char**);

bool IRC_ProcessCommand(char* channel, unsigned int partc, char **command)
{
	unsigned int i;
	for(i = 0; i < sizeof(CMD_list)/8;++i)
	{
		if(!strcmp((char*)(CMD_list[i][0]), &command[0][2]))
		{
			cmd = CMD_list[i][1];
			cmd(channel, partc-4, &command[1]);
			return true;
		}
	}
	return false;
}
