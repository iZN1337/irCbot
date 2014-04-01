/**
 * @project: CBot - An Internet Relay Chat bot written in c
 * @file: main.c
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#include "main.h"

int main()
{
    if (!IRC_AttemptConnection("94.242.253.75", 6667))
    {
        printf("Connection failed!\nPress any key to continue...");
        getchar();
    }

    return 0;
}
