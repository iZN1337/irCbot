/**
<<<<<<< HEAD
 * @project: irCbot - An Internet Relay Chat bot written in c
=======
 * @project: irCbot - An Internet Relay Chat bot written in C
>>>>>>> 4196396a9e9db972a14464e8ebb5f42ba47a200e
 * @file: utils.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "utils.h"

unsigned int explode(char *pStr, char **pOut, const char *pDelim)
{
    unsigned int
        i = 0;
    pOut[0] = strtok(pStr, pDelim);

    while((pOut[++i] = strtok(NULL, pDelim)) != NULL);

    return i;
}
