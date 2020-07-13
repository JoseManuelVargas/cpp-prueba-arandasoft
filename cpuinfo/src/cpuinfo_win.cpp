#include "cpuinfo.h"
#include <windows.h>


CPUInfo getCPUInfo() {
	CPUInfo cpu_info;
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	cpu_info.cores = siSysInfo.dwNumberOfProcessors;
	LARGE_INTEGER cpuFreq;
	QueryPerformanceFrequency(&cpuFreq);
	DWORD logInfoLen;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION logInfo;
	GetLogicalProcessorInformation(&logInfo, &logInfoLen);
	switch (siSysInfo.wProcessorArchitecture) {
		case PROCESSOR_ARCHITECTURE_AMD64:
			cpu_info.name = "x64 (AMD or Intel)";
			break;
		case PROCESSOR_ARCHITECTURE_ARM:
			cpu_info.name = "ARM";
			break;
		case PROCESSOR_ARCHITECTURE_ARM64:
			cpu_info.name = "ARM64";
			break;
		case PROCESSOR_ARCHITECTURE_IA64:
			cpu_info.name = "Intel Itanium-based";
			break;
		case PROCESSOR_ARCHITECTURE_INTEL:
			cpu_info.name = "x86 ";
			break;
		case PROCESSOR_ARCHITECTURE_UNKNOWN:
			cpu_info.name = "Unknown architecture";
			break;
	}
	cpu_info.cache_size = logInfo.Cache.Size / 1024;
	cpu_info.frequency = cpuFreq.QuadPart;
	return cpu_info;
}

