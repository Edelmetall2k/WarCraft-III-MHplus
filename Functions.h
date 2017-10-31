#pragma once

void Patch(DWORD dwBaseAddress, char *szData, int iSize);

void PlantDetourCall(BYTE *bSource, BYTE *bDestination, int iLength);
void PlantDetourJump(BYTE *bSource, BYTE *bDestination, int iLength);