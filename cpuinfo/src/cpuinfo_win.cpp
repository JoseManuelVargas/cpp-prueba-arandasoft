#include "cpuinfo.h"
//#include <windows.h>
#include <stdio.h>
//#pragma comment(lib, "user32.lib")


CPUInfo getCPUInfo() {
	CPUInfo cpu_info;
	//SYSTEM_INFO siSysInfo;
	//GetSystemInfo(&siSysInfo);
	//cpu_info.cores = siSysInfo.dwNumberOfProcessors;
	cpu_info.name = "Error Name";
	cpu_info.cores = 4;
	cpu_info.cache_size = 2;
	cpu_info.frequency = 3000;
	return cpu_info;
}

