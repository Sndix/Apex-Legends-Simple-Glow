#include "Utility.h"


MODULEENTRY32 mEntry;
HANDLE hProc;
DWORD pid;
DWORD64 Base;
HWND hwnd;
DWORD64 GetModule(const char* lModule, DWORD dwPID)
{
	HANDLE hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwPID);
	mEntry.dwSize = sizeof(MODULEENTRY32);

	do
	{
		if (!strcmp(mEntry.szModule, lModule))
		{
			CloseHandle(hModule);
			return (DWORD_PTR)mEntry.modBaseAddr;
		}
	} while (Module32Next(hModule, &mEntry));

	CloseHandle(hModule);
	return 0;
}


DWORD64 GetBase() {
	hwnd = FindWindow(NULL, "Apex Legends"); // Get the Window of the Process
	GetWindowThreadProcessId(hwnd, &pid); // Get the Process ID of the Process;
	Base = GetModule("r5apex.exe", pid); // Getting the Process Base address using the pid
	hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); // Gain full Access on the process.

	return Base;
}


DWORD64 RPM64(DWORD64 Offset) {
	DWORD64 Buffer;
	ReadProcessMemory(hProc, (LPVOID)Offset, &Buffer, sizeof(DWORD64), NULL);
	return Buffer;
}
void WPMBool(DWORD64 Offset,bool value) {
	WriteProcessMemory(hProc, (LPVOID)Offset, &value, sizeof(float), NULL);
}
void WPMFloat(DWORD64 Offset, float value) {
	WriteProcessMemory(hProc, (LPVOID)Offset, &value, sizeof(float), NULL);
}
void WPMInt(DWORD64 Offset, int value) {
	WriteProcessMemory(hProc, (LPVOID)Offset, &value, sizeof(float), NULL);
}
std::string RPMString(DWORD64 Offset) {
	std::string Buffer;
	ReadProcessMemory(hProc, (LPVOID)Offset, &Buffer, sizeof(DWORD64), NULL);
	return Buffer;
}