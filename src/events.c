/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: events.c
 * @author: Djole, King_Hual &lt;djolel@net.dut.edu.vn&gt;, &lt;king_hell@abv.bg&gt;
 */

#include "events.h"

void IRC_ProcessEvents(char *pLine)
{
    char **pParts;
    unsigned int iSize;

    iSize = explode(&pParts, pLine, ' ');

    printf("%s\r\n", pLine);

    if (pParts[0] && pParts[1])
    {
        if (!strcmp(pParts[0], "PING"))
        {
            IRC_SendRaw("PONG %s", pParts[1]);
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
                        IRC_ProcessCommand(&pParts[0][1], pParts[2], iSize, &pParts[3], IRC_GetParameterAt(pLine, 4));
                    break;
                }
                default:
                {
                    if (pParts[3][1] == '\x01')
                    {
                        if (!strncmp(pParts[3] + 2, "VERSION", 7))
                        {
                            IRC_SendRaw("PRIVMSG #no :version fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "TIME", 4))
                        {
                            IRC_SendRaw("PRIVMSG #no :time fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "FINGER", 6))
                        {
                            IRC_SendRaw("PRIVMSG #no :finger fr");
                        }
                        else if (!strncmp(pParts[3] + 2, "PING", 4))
                        {
                            IRC_SendRaw("PRIVMSG #no :ping fr");
                        }
                    }
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
    IRC_SendRaw("NICK %s_tmp", ConfigVal(CONFIG_VALUE_NICK));
}

void IRC_OnBotConnect()
{
    IRC_SendRaw("JOIN %s", ConfigVal(CONFIG_VALUE_CHANNELS));
}
