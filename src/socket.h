/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: socket.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#ifndef SOCKET_H_INCLUDED
	#define SOCKET_H_INCLUDED

#include "stdafx.h"

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?

	#define WIN32_LEAN_AND_MEAN
	#include <winsock2.h>
	#if (defined _MSC_VER)
		#pragma comment (lib, "Ws2_32.lib")
	#endif
#else
	#include <sys/socket.h>
	#include <netdb.h>
	#include <sys/stat.h>
	#include <netinet/in.h>
	#include <unistd.h>
	#include <errno.h>
	#include <arpa/inet.h>

	#define closesocket(s) close(s)
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1

	typedef unsigned int SOCKET;

#endif

SOCKET iSocket; // unsigned int

int IRC_AttemptConnection(const char *szAddress, int iPort);
int IRC_SendRaw(char *szRawCommand, ...);
THREAD_CALLBACK IRC_ProcessDataThread(void* lpParam); // pointer to a threaded function

#endif // SOCKET_H_INCLUDED
