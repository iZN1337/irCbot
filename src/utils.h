/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: utils.h
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: Add IRC_ReadFile
 */
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include "stdafx.h"

unsigned int explode(char *pStr, char **pOut, const char *pDelim);
void GetNameFromPath(char* out, const char* path, const char* name);
char* IRC_ReadFile(const char* pPath);

#endif // UTILS_H_INCLUDED
