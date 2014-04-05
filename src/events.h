/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include "stdafx.h"
#include "socket.h"

void IRC_ProcessEvents(char *pLine);
void IRC_OnNicknameConflict();
void IRC_OnBotConnect();

#endif
