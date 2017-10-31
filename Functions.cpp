#include "Warcraft.h"

void Patch(DWORD dwBaseAddress, char *szData, int iSize)
{
	DWORD dwOldProtection = NULL;
	
	VirtualProtect((LPVOID)dwBaseAddress, iSize, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	CopyMemory((LPVOID)dwBaseAddress, szData, iSize);
	VirtualProtect((LPVOID)dwBaseAddress, iSize, dwOldProtection, NULL);
}

void PlantDetourCall(BYTE *bSource, BYTE *bDestination, int iLength)
{
	DWORD dwOldProtection = NULL;

	BYTE *bJump = (BYTE *)malloc(iLength + 5);

	VirtualProtect(bSource, iLength, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy(bJump + 3, bSource, iLength);

	bJump[0] = 0x58;
	bJump[1] = 0x59;
	bJump[2] = 0x50;
	bJump[iLength + 3] = 0xE9;
	*(DWORD *)(bJump + iLength + 4) = (DWORD)((bSource + iLength) - (bJump + iLength + 3)) - 5;

	bSource[0] = 0xE8;
	*(DWORD *)(bSource + 1) = (DWORD)(bDestination - (bSource)) - 5;

	for (int i = 5; i < iLength; i++)
		bSource[i] = 0x90;

	VirtualProtect(bSource, iLength, dwOldProtection, NULL);
}

void PlantDetourJump(BYTE *bSource, BYTE *bDestination, int iLength)
{
	DWORD dwOldProtection = NULL;

	BYTE *bJump = (BYTE *)malloc(iLength + 5);

	VirtualProtect(bSource, iLength, PAGE_EXECUTE_READWRITE, &dwOldProtection);
	memcpy(bJump, bSource, iLength);

	bJump[iLength] = 0xE9;
	*(DWORD *)(bJump + iLength) = (DWORD)((bSource + iLength) - (bJump + iLength)) - 5;

	bSource[0] = 0xE9;
	*(DWORD *)(bSource + 1) = (DWORD)(bDestination - bSource) - 5;

	for (int i = 5; i < iLength; i++)
		bSource[i] = 0x90;

	VirtualProtect(bSource, iLength, dwOldProtection, NULL);
}
