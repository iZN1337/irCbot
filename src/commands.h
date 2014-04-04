/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: commands.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

#include "stdafx.h"

#define CMD_S(cmd) (void*)(cmd)
#define CMD_F(cmd) (&cmd)
#define CMD_LIST void* CMD_list[][2] =

extern void* CMD_string[][2]; // for later use in other files

bool IRC_ProcessCommand(char* channel, unsigned int partc, char **command);

#endif // COMMANDS_H_INCLUDED
