/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.c
 * @authors: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 */

#include "events.h"

void IRC_ProcessEvents(INSTANCE iInstance, char *pLine)
{
    char **pParts;
    unsigned int iSize;

    iSize = explode(&pParts, pLine, ' ');

    printf("%s\r\n", pLine);

    if (pParts[0] && pParts[1])
    {
        if (!strcmp(pParts[0], "PING"))
        {
            IRC_SendRaw(iInstance, "PONG %s", pParts[1]);
        }
        else if (!strcmp(pParts[1], "JOIN"))
        {

        }
        else if (!strcmp(pParts[1], "PART"))
        {

        }
        else if (!strcmp(pParts[1], "KICK"))
        {

        }
        else if (!strcmp(pParts[1], "QUIT"))
        {

        }
        else if (!strcmp(pParts[1], "MODE"))
        {

        }
        else if (!strcmp(pParts[1], "NICK"))
        {

        }
        else if (!strcmp(pParts[1], "TOPIC"))
        {

        }
        else if (!strcmp(pParts[1], "NOTICE"))
        {

        }
        else if (!strcmp(pParts[1], "PRIVMSG"))
        {
            switch (pParts[2][0])
            {
                case '#':
                case '+':
                case '%':
                case '@':
                {
                    if (pParts[3][1] == ConfigVal(CONFIG_VALUE_PREFIX)[0])
                        IRC_ProcessCommand(iInstance, &pParts[0][1], pParts[2], iSize, &pParts[3], IRC_GetParameterAt(pLine, 4));
                    break;
                }
                default:
                {
                    if (pParts[3][1] == '\x01')
                    {
                        if (!strncmp(pParts[3] + 2, "VERSION", 7))
                        {
                            IRC_SendRaw(iInstance, "PRIVMSG #no :version fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "TIME", 4))
                        {
                            IRC_SendRaw(iInstance, "PRIVMSG #no :time fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "FINGER", 6))
                        {
                            IRC_SendRaw(iInstance, "PRIVMSG #no :finger fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "PING", 4))
                        {
                            IRC_SendRaw(iInstance, "PRIVMSG #no :ping fr");
                        }
                    }
                }
            }
        }
        else if (!strcmp(pParts[1], "ERROR"))
        {
        	
            // re-connect
        }
        else
        {
            if (!strcmp(pParts[1], "001"))
            {
                IRC_OnBotConnect(iInstance);
            }
            else if (!strcmp(pParts[1], "433"))
            {
                IRC_OnNicknameConflict(iInstance);
            }
        }
    }

    free(pParts);
}

void IRC_OnNicknameConflict(INSTANCE iInstance)
{
    IRC_SendRaw(iInstance, "NICK %s`%d", ConfigVal(CONFIG_VALUE_NICK), rand() % 0xFFFF);
}

void IRC_OnBotConnect(INSTANCE iInstance)
{
    char **pPerform;
    int iSize, iIdx;

	IRC_SendRaw(iInstance, "JOIN %s", ConfigVal(CONFIG_VALUE_CHANNELS));

    iSize = explode(&pPerform, ConfigVal(CONFIG_VALUE_PERFORM), '~');
    for (iIdx = 0; iIdx != iSize; ++ iIdx)
        IRC_SendRaw(iInstance, pPerform[iIdx]);
}
