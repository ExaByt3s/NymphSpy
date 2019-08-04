#pragma once

#include "../Core.h"

struct NYMPHCORE_PHYSICAL_PROCESS {
	sdk::string name;
	DWORD id;
};

namespace Process {

	DWORD GetProcessID(HWND hwDescriptor);
	DWORD GetProcessID(HANDLE hProcess);
	DWORD GetProcessID(const char* processName);

	bool Alive(DWORD ProcessID);
	bool Alive(HANDLE hProcess);
	bool Alive(const char* processName);

	bool Kill(DWORD ProcessID);
	bool Kill(HANDLE hProcess);
	bool Kill(const char* processName);

	DWORD GetExplorerPID();
	sdk::list<NYMPHCORE_PHYSICAL_PROCESS> List();

}