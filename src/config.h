/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */
#ifndef CONFIG_H_INCLUDED
	#define CONFIG_H_INCLUDED

#include "stdafx.h"

#define CONFIG_VALUE_SERVER		(0)
#define CONFIG_VALUE_PORT		(1)
#define CONFIG_VALUE_SSL		(2)
#define CONFIG_VALUE_NICK		(3)
#define CONFIG_VALUE_USER		(4)
#define CONFIG_VALUE_REAL		(5)
#define CONFIG_VALUE_CMDDELIM	(6)
#define CONFIG_VALUE_CHANNELS	(7)
#define CONFIG_VALUE_PERFORM	(8)

#define ConfigVal(i) ppConfig[i]

#define INI_MAX_KEYS 9

extern char *ppConfig[INI_MAX_KEYS];

int IRC_SetupConfig(const char *szLocation);

#endif // CONFIG_H_INCLUDED
