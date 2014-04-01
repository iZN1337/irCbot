/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: main.h
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdio.h>

enum
{
    // http://www.irc.org/tech_docs/005.html
    MAX_HOSTNAME_LENGTH = 255;
    MAX_NICKNAME_LENGTH = 30;
    MAX_CHANNEL_LENGTH = 50;
    MAX_BOT_CHANNELS = 25;

};

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
#endif // MAIN_H_INCLUDED
