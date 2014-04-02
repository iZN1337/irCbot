/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "stdafx.h"

unsigned int explode(char *szStr, char **ppOut, const char *szDelim); // splits szStr into ppOut, using szDelim as a delimiter
char* GetApplicationPath(char* szMargv0); // gets the application path
void GetNameFromPath(char* lpOut, const char* szPath, const char* szName); // appends a filename to the specified path
signed int GetKeyIndex(const char** ppKeys, const char* szKey); // gets the index of a string that matches a given string
char* IRC_ReadFile(const char* szPath); // reads a file, without streaming, and returns a pointer to the string (only to be used for small files)
char* trim(char* szString);
char* replace_first(char* szString, const char cChr, const char cReplacement);

#endif // UTILS_H_INCLUDED
