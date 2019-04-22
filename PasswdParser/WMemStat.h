#pragma once
#include <windows.h>
#include <psapi.h>





class WMemStat
{
private:
	MEMORYSTATUSEX memInfo;
	PROCESS_MEMORY_COUNTERS_EX pmc;


public:
	size_t Total_Virtual_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullTotalPageFile;
	}

	size_t Avalible_Virtual_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullAvailPageFile;
	}

	size_t Current_Used_Virtual_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullTotalPageFile - memInfo.ullAvailPageFile;
	}

	size_t CurrProc_Used_Virtual_Memory() {
		GetProcessMemoryInfo(
			GetCurrentProcess(),
			(PROCESS_MEMORY_COUNTERS*)&pmc,
			sizeof(pmc)
		);
		return pmc.PrivateUsage;
	}


public:
	size_t Total_Physical_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullTotalPhys;
	}

	size_t Avalible_Physical_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullAvailPhys;
	}

	size_t Current_Used_Physical_Memory() {
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullTotalPhys - memInfo.ullAvailPhys;
	}

	size_t CurrProc_Used_Physical_Memory() {
		GetProcessMemoryInfo(
			GetCurrentProcess(),
			(PROCESS_MEMORY_COUNTERS*)&pmc,
			sizeof(pmc)
		);
		return pmc.WorkingSetSize;
	}


public:
	WMemStat() {
		memInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memInfo);
	}

	~WMemStat() {}
};

