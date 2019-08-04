#include "../Includes/Process.h"

DWORD Process::GetProcessID(HWND hwDescriptor) {
	DWORD pID = 0x0;
	GetWindowThreadProcessId(hwDescriptor, &pID);
	return pID;
}

DWORD Process::GetProcessID(HANDLE hProcess) {
	return GetProcessId(hProcess);
}

DWORD Process::GetProcessID(const char* processName) {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!strcmp(processName, processInfo.szExeFile)) {
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo)) {
		if (!strcmp(processName, processInfo.szExeFile)) {
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

bool Process::Alive(DWORD ProcessID) {
	DWORD dwExitCode = 0;
	GetExitCodeProcess(OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ProcessID), &dwExitCode);
	return dwExitCode == STILL_ACTIVE;
}

bool Process::Alive(HANDLE hProcess) {
	DWORD dwExitCode = 0;
	GetExitCodeProcess(hProcess, &dwExitCode);
	return dwExitCode == STILL_ACTIVE;
}

bool Process::Alive(const char* processName) {
	DWORD dwExitCode = 0;
	GetExitCodeProcess(OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, GetProcessID(processName)), &dwExitCode);
	return dwExitCode == STILL_ACTIVE;
}

bool Process::Kill(DWORD ProcessID) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, ProcessID);
	return TerminateProcess(hProcess, 0);
}

bool Process::Kill(HANDLE hProcess) {
	return TerminateProcess(hProcess, 0);
}

bool Process::Kill(const char* processName) {
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, false, Process::GetProcessID(processName));
	return TerminateProcess(hProcess, 0);
}

DWORD Process::GetExplorerPID() {
	DWORD pID = 0;
	HWND hwExplorer;
	if (hwExplorer = FindWindowA("Shell_TrayWnd", NULL)) { GetWindowThreadProcessId(hwExplorer, &pID); }
	if (pID == 0) { pID = GetProcessID("explorer.exe"); }
	return pID;
}

sdk::list<NYMPHCORE_PHYSICAL_PROCESS> Process::List() {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	sdk::list<NYMPHCORE_PHYSICAL_PROCESS>* processList = new sdk::list<NYMPHCORE_PHYSICAL_PROCESS>;

	HANDLE processSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processSnapshot == INVALID_HANDLE_VALUE)
		return *processList;

	if (Process32First(processSnapshot, &processInfo)) {
		do {
			processList->append({ (char*)processInfo.szExeFile, processInfo.th32ProcessID });
		} while (Process32Next(processSnapshot, &processInfo));
		CloseHandle(processSnapshot);
	} return *processList;
}