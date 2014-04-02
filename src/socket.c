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
    char szBuffer[4096], *pParts[35];

    IRC_SendRaw("NICK myCBot_\r\n"); // send the NICK command
    IRC_SendRaw("USER myCBot_ * * :myCBot_\r\n"); // register with daemon

    while ((iRecvSize = recv(iSocket, szBuffer, sizeof (szBuffer), 0))) // receive stream response, 4096 bytes at a time
    {
		szBuffer[iRecvSize] = '\0'; // zero-terminated
		printf("%s\r\n", szBuffer); // print line to console
		explode(szBuffer, pParts, " "); // split parameters
		if (!strcmp(pParts[0], "PING")) // if first parameter is PING
			IRC_SendRaw("PONG %s\r\n", pParts[1]); // send PONG
    }

    return 0;
}
