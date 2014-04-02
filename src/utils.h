/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "stdafx.h"

unsigned int explode(char *szStr, char **ppOut, const char *szDelim);
char* GetApplicationPath(char* szMargv0);
void GetNameFromPath(char* lpOut, const char* szPath, const char* szName);
signed int GetKeyIndex(const char** ppKeys, const char* szKey);
char* IRC_ReadFile(const char* szPath);

#endif // UTILS_H_INCLUDED
