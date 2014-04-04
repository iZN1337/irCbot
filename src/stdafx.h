/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: stdafx.h
 * @author: Djole, King_Hual <djolel@net.dut.edu.vn>, <king_hell@abv.bg>
 * @last update: N/A
 */

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
	#define _WIN32_WINNT 0x0501
	#include <windows.h>
#else
	typedef void* HANDLE;
#endif

#define true 1
#define false 0
typedef unsigned char bool;

#include "constants.h"
#include "utils.h"
#include "config.h"
#include "thread.h"
#include "events.h"
#include "commands.h"
