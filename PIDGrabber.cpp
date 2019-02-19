#include <pch.h>
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

using namespace std;

int getID(wstring processName) {

	int pid = 0;

	std::vector<DWORD> pids;
	std::wstring targetProcessName = processName;

	HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes

	PROCESSENTRY32W entry; //current process
	entry.dwSize = sizeof entry;

	if (!Process32FirstW(snap, &entry)) { //start with the first in snapshot
		return 0;
	}

	do {
		if (std::wstring(entry.szExeFile) == targetProcessName) {
			pids.emplace_back(entry.th32ProcessID); //name matches; add to list
		}
	} while (Process32NextW(snap, &entry)); //keep going until end of snapshot

	for (int i(0); i < pids.size(); ++i) {
		std::cout << pids[i] << std::endl;
		pid = pids[i];
	}

	return pid;
}

int main() {
	wstring procName = L"Blitz.exe";
	int pid = getID(procName);

	cout << "The PID is: " << pid << endl;

	system("pause");
}