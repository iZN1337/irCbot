/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: socket.c
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#include "socket.h"
int IRC_AttemptConnection(const char *szAddress, int iPort)
{
	#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
        WSADATA iWsa; // WSA stuff, windows-only
        if (WSAStartup(MAKEWORD(2, 2), &iWsa) != 0)
            return 1;
	#endif
        if ((iSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET) // initialize socket, sore in iSocket
        {
            struct sockaddr_in iServices; // initialize a sockaddr_in struct

            iServices.sin_family = AF_INET; // must be AF_INET (internet)
            iServices.sin_port = htons(iPort); // convert port to unsigned short
            iServices.sin_addr.s_addr = inet_addr(szAddress); // convert ipv4 address to an unsigned long

            if (!connect(iSocket, (struct sockaddr *) &iServices, sizeof (iServices))) // connect to the socket
            {
                THANDLE iCoreThread; // declare a THANDLE
                bool bSuccess = StartThread(&iCoreThread, IRC_ProcessDataThread, NULL); // start IRC_ProcessDataThread in a new thread
                WaitForThread(iCoreThread); // wait for the thread to finish before proceeding further
                return bSuccess;
            }
        }
	closesocket(iSocket); // close the socket
    #if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
        WSACleanup(); // wsa cleanup, windows only
    #endif
    return 0;
}

int IRC_SendRaw(char *szRawCommand, ...) // send a raw formatted message
{
    char szBuffer[512];

    va_list iVa;
    va_start(iVa, szRawCommand);
    vsprintf(szBuffer, szRawCommand, iVa);
    va_end(iVa);

    return send(iSocket, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

THREAD_CALLBACK IRC_ProcessDataThread(void* lpParam)
{
    size_t iRecvSize;
    char szBuffer[4096], **pParts;
    int iSize;

    IRC_SendRaw("NICK myCBot_\r\n"); // send the NICK command
    IRC_SendRaw("USER myCBot_ * * :myCBot_\r\n"); // register with daemon
    while ((iRecvSize = recv(iSocket, szBuffer, sizeof (szBuffer), 0))) // receive stream response, 4096 bytes at a time
    {
	szBuffer[iRecvSize] = '\0'; // zero-terminated
	printf("%s\r\n", szBuffer);
	iSize = explode(&pParts, szBuffer, ' '); // split parameters

	if (pParts[0] && pParts[1])
        {
            if (!strcmp(pParts[0], "PING"))
            {
                IRC_SendRaw("PONG %s\r\n", pParts[1]);
                continue;
            }
            else if (!strcmp(pParts[1], "JOIN"))
            {
                printf("IRC_OnJoin event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "PART"))
            {
                printf("IRC_OnPart event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "KICK"))
            {
                printf("IRC_OnKick event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "QUIT"))
            {
                printf("IRC_OnQuit event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "MODE"))
            {
                printf("IRC_OnMode event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "NICK"))
            {
                printf("IRC_OnNick event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "TOPIC"))
            {
                printf("IRC_OnTopic event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "NOTICE"))
            {
                printf("IRC_OnNotice event\r\n");
                continue;
            }
            else if (!strcmp(pParts[1], "PRIVMSG"))
            {
                if (pParts[2][0] == '#')
                {
                    printf("CHANNEL MESSAGE!\r\n");

                    if (pParts[3][1] == '!')
                    {
                        printf("COMMAND DETECTED: %s\r\n", strstr(pParts[3], "!"));
                        // just for testing
                        // no command handler added yet.
                        if (!strcasecmp(strstr(pParts[3], "!"), "!say"))
                        {
                            int i;
                            char szParams[128];
                            szParams[0] = '\0';
                            for (i = 4; i != iSize; ++ i)
                            {
                                strcat(szParams, pParts[i]);
                                strcat(szParams, " ");
                            }
                            IRC_SendRaw("PRIVMSG %s :%s\r\n", pParts[2], szParams);
                            continue;
                            /*
                            if (pParts[4])
                            {
                                printf("inside parts 4\r\n");
                                int i;
                                char *pParams;
                                pParams = (char*)malloc(sizeof (pParts[iSize]));
                                pParams[0] = '\0';
                                for (i = 4; i != iSize; ++ i)
                                {
                                    printf("inside loop\r\n");
                                    strcat(pParams, pParts[i]);
                                    strcat(pParams, " ");
                                }
                                printf("params: %s\r\n", pParams);
                                IRC_SendRaw("PRIVMSG %s :%s\r\n", pParts[2], pParams);
                                free(pParams);
                            }
                            else
                            {
                                IRC_SendRaw("PRIVMSG %s :No params given.\r\n", pParts[2]);
                            }
                            */
                        }
                    }
                }
                else
                {
                    printf("PRIVATE MESSAGE!\r\n");
                    continue;
                }
            }
            else if (!strcmp(pParts[1], "ERROR"))
            {
                printf("IRC_OnError event\r\n");
                continue;
            }
            else
            {
                printf("=> %s\r\n", pParts[1]);
                if (!strcmp(pParts[1], "001"))
                {
                    IRC_SendRaw("JOIN #no\r\n");
                    continue;
                }
                else if (!strcmp(pParts[1], "433"))
                {
                    // nick name conflict
                    continue;
                }
            }
        }
        free(pParts);
    }
    return 0;
}

