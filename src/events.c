/**
* @project: irCbot - An Internet Relay Chat bot written in C
* @file: events.c
* @author: Djole, King_Hual &lt;djolel@net.dut.edu.vn&gt;, &lt;king_hell@abv.bg&gt;
* @last update: N/A
*/

#include "events.h"

void IRC_ProcessEvents(char *pLine)
{
    char **pParts;
    unsigned int iSize;
    printf("%s\r\n", pLine);
    iSize = explode(&pParts, pLine, ' ');

    if (pParts[0] && pParts[1])
    {
        if (!strcmp(pParts[0], "PING"))
        {
            IRC_SendRaw("PONG %s\r\n", pParts[1]);
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
                        IRC_ProcessCommand(pParts[2], iSize, &pParts[3]);
                    break;
                }
                default:
                {
                    // private message
                }
            }
        }
        else if (!strcmp(pParts[1], "ERROR"))
        {
            // rip
        }
        else
        {
            if (!strcmp(pParts[1], "001"))
            {
                IRC_OnBotConnect();
            }
            else if (!strcmp(pParts[1], "433"))
            {
                IRC_OnNicknameConflict();
            }
        }
    }

    free(pParts);
}

void IRC_OnNicknameConflict()
{
    IRC_SendRaw("NICK %s_tmp\r\n", ConfigVal(CONFIG_VALUE_NICK));
}

void IRC_OnBotConnect()
{
    IRC_SendRaw("JOIN %s\r\n", ConfigVal(CONFIG_VALUE_CHANNELS));
}
