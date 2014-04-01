/**
 * @project: CBot - An Internet Relay Chat bot written in c
 * @file: socket.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "socket.h"
int IRC_AttemptConnection(const char *szAddress, int iPort)
{
    WSADATA
        iWsa;

    if (WSAStartup(MAKEWORD(2, 2), &iWsa) == 0)
    {
        if ((iSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
        {
            struct
                sockaddr_in iServices;

            iServices.sin_family = AF_INET;
            iServices.sin_port = htons(iPort);
            iServices.sin_addr.s_addr = inet_addr(szAddress);

            if (!connect(iSocket, (struct sockaddr *) &iServices, sizeof (iServices)))
            {
                HANDLE iCoreThread = CreateThread(NULL, 0, IRC_ProcessDataThread, NULL, 0, NULL);
                WaitForSingleObject(iCoreThread, INFINITE);

                return iCoreThread != NULL;
            }
        }
    }
    closesocket(iSocket);
    WSACleanup();

    return 0;
}

int IRC_SendRaw(char *szRawCommand, ...)
{
    char szBuffer[512];

    va_list iVa;
    va_start(iVa, szRawCommand);
    vsprintf(szBuffer, szRawCommand, iVa);
    va_end(iVa);

    return send(iSocket, szBuffer, strlen(szBuffer), 0) != SOCKET_ERROR;
}

DWORD WINAPI IRC_ProcessDataThread(LPVOID lpParam)
{
    size_t
        iRecvSize;
    char
        szBuffer[4096], *pParts[35];

    IRC_SendRaw("NICK myCBot_\r\n");
    IRC_SendRaw("USER myCBot_ * * :myCBot_\r\n");

    while ((iRecvSize = recv(iSocket, szBuffer, sizeof (szBuffer), 0)))
    {
        if (iRecvSize && iRecvSize <= sizeof (szBuffer))
        {
            szBuffer[iRecvSize] = '\0';
            printf("%s\r\n", szBuffer);
            explode(szBuffer, pParts, " ");
            if (!strcmp(pParts[0], "PING"))
                IRC_SendRaw("PONG %s\r\n", pParts[1]);
        }
    }

    return 0;
}
