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

	struct sockaddr_in iServices; // initialize the structures
	struct addrinfo aiHints, *aiAddrinfo = NULL;

	memset(&aiHints, 0, sizeof(aiHints)); // set aiHints properties
	aiHints.ai_family = AF_INET;
	aiHints.ai_socktype = SOCK_STREAM;
	aiHints.ai_protocol = IPPROTO_TCP;

	if ((iSocket = socket(aiHints.ai_family, aiHints.ai_socktype, aiHints.ai_protocol)) != INVALID_SOCKET) // initialize socket, sore in iSocket
	{
		getaddrinfo(szAddress, NULL, &aiHints, &aiAddrinfo); // resolve IP from hostname
		memcpy(&iServices,aiAddrinfo->ai_addr,sizeof(iServices)); // copy to the sockaddr_in structure
		freeaddrinfo(aiAddrinfo); // free memory

		iServices.sin_port = htons(iPort); // set the port

		if (!connect(iSocket, (struct sockaddr*)&iServices, sizeof (iServices))) // connect to the socket
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
    char szBuffer[512], szLines[1024], *lastLine, *pLine, *pNextLine;

    IRC_SendRaw("NICK myCBot_\r\n"); // send the NICK command
    IRC_SendRaw("USER myCBot_ * * :myCBot_\r\n"); // register with daemon

    while ((iRecvSize = recv(iSocket, szBuffer, sizeof (szBuffer), 0))) // receive stream response, 512 bytes at a time
    {
		szBuffer[iRecvSize] = '\0'; // zero-terminated

		strcat(szLines, szBuffer);
		pLine = szLines;
		lastLine = strrchr(szLines, '\r');
		*lastLine = *(lastLine+1) = 0;

		do
		{
			pNextLine = strchr(pLine, '\r');
			if(pNextLine)
				*pNextLine = *(pNextLine+1) = 0;

			/** use pLine here **/

			IRC_ProcessEvents(pLine);

			/** stop using pLine here **/

			pLine = pNextLine+2;
		}
		while(pNextLine && strlen(pLine));

		strcpy(szLines, lastLine+2);
    }
    return 0;
}

