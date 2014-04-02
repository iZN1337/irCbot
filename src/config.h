/**
 * @project: irCbot - An Internet Relay Chat bot written in C
 * @file: config.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#ifndef CONFIG_H_INCLUDED
	#define CONFIG_H_INCLUDED

#include "stdafx.h"

/* configuration definitions, to be used in ConfigVal */

#define CONFIG_VALUE_SERVER		(0)
#define CONFIG_VALUE_PORT		(1)
#define CONFIG_VALUE_SSL		(2)
#define CONFIG_VALUE_NICK		(3)
#define CONFIG_VALUE_USER		(4)
#define CONFIG_VALUE_REAL		(5)
#define CONFIG_VALUE_CMDDELIM	(6)
#define CONFIG_VALUE_CHANNELS	(7)
#define CONFIG_VALUE_PERFORM	(8)

#define ConfigVal(i) ppConfig[i] // fetch a value from configuration using one of the CONFIG_VALUE definitions

#define INI_MAX_KEYS 9 // configuration properties count

extern char *ppConfig[INI_MAX_KEYS]; // global pointer array (hence extern), stores configuration values

int IRC_SetupConfig(const char *szLocation); // IRC_SetupConfig method, used to load the configuration from the file

#endif // CONFIG_H_INCLUDED
