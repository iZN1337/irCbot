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
        WSADATA iWsa;
        if (WSAStartup(MAKEWORD(2, 2), &iWsa) != 0)
            return 1;
	#endif
        if ((iSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != INVALID_SOCKET)
        {
            struct sockaddr_in iServices;

            iServices.sin_family = AF_INET;
            iServices.sin_port = htons(iPort);
            iServices.sin_addr.s_addr = inet_addr(szAddress);

            if (!connect(iSocket, (struct sockaddr *) &iServices, sizeof (iServices)))
            {
                THANDLE iCoreThread;
                bool bSuccess = StartThread(&iCoreThread, IRC_ProcessDataThread, NULL);
                WaitForThread(iCoreThread);
                return bSuccess;
            }
        }
	closesocket(iSocket);
    #if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
        WSACleanup();
    #endif
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

THREAD_CALLBACK IRC_ProcessDataThread(void* lpParam)
{
    size_t iRecvSize;
    char szBuffer[4096], *pParts[35];

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
