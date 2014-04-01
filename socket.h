/**
 * @project: CBot - An Internet Relay Chat bot written in c
 * @file: socket.h
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#ifndef SOCKET_H_INCLUDED
#define SOCKET_H_INCLUDED

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdarg.h>
// #pragma comment(lib, "ws2_32.lib")

SOCKET
    iSocket;

int IRC_AttemptConnection(const char *address, int port);
int IRC_SendRaw(char *szRawCommand, ...);
DWORD WINAPI IRC_ProcessDataThread(LPVOID lpParam);

#endif // SOCKET_H_INCLUDED
