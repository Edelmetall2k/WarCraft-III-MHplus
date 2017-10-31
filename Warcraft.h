#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>

const HWND  hWnd      = FindWindow("Warcraft III", NULL);
const DWORD dwGameDll = (DWORD)GetModuleHandle("Game.dll");

#include "Functions.h"