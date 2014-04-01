/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: constants.h
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include "stdafx.h"

#define MAX_HOSTNAME_LENGTH (255)
#define MAX_NICKNAME_LENGTH (30)
#define MAX_CHANNEL_LENGTH (50)
#define MAX_BOT_CHANNELS (25)

struct IRC_Settings
{
    char szConnectedTo[MAX_HOSTNAME_LENGTH];
    int iPort;
    int iSSL;
    char szNickname[MAX_NICKNAME_LENGTH];
    char szUsername[MAX_NICKNAME_LENGTH];
    char szRealname[MAX_NICKNAME_LENGTH];
    char szChannels[MAX_BOT_CHANNELS][MAX_CHANNEL_LENGTH];
};

#endif // CONSTANTS_H_INCLUDED
