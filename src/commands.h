/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "stdafx.h"

#define CMDDEF(cmd) { (#cmd), (CMD_##cmd) }
#define CMD_LIST static struct CMDstruct CMDlist[] =
#define CMD(cmd) static void CMD_##cmd(char* user, char* channel, unsigned int argc, char** args, char* args_raw)

struct CMDstruct
{
	char* str;
	void (*func)(char*, char*, unsigned int, char**, char*);
};

bool IRC_ProcessCommand(char* user, char* channel, unsigned int partc, char **command, char* raw);

#endif // COMMANDS_H_INCLUDED
