#include "Warcraft.h"

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		Patch(dwGameDll + 0x210341, "\x66\x83\xC9\x0F", 4);
		Patch(dwGameDll + 0x2107B5, "\x66\x83\xCA\x0F", 4);
		//When MH off:
		//Patch(dwGameDll + 0x210341, "\x66\x0B\x0C\x50", 4);
		//Patch(dwGameDll + 0x2107B5, "\x66\x0B\x14\x70", 4);
	}

	return TRUE;
}