/**
 * @project: irCbot - An Internet Relay Chat bot written in c
 * @file: stdafx.h
 * @author: Djole, King_Hual <pop96x@gmail.com>, <>
 * @last update: N/A
 */
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64)) // is it a windows build?
	#include <windows.h>
#else
	typedef void* HANDLE;
#endif

// bool-related

#define true 1
#define false 0
typedef unsigned char bool;

#include "constants.h"
#include "utils.h"
#include "thread.h"
