#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>


DWORD64 GetBase();
DWORD64 RPM64(DWORD64 Offset);
std::string RPMString(DWORD64 Offset);

void WPMBool(DWORD64 Offset, bool value);
void WPMFloat(DWORD64 Offset, float value);
void WPMInt(DWORD64 Offset, int value);
