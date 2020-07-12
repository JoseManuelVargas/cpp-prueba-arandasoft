#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <sys/sysctl.h>
#include "cpuinfo.h"

using namespace std;


CPUInfo getCPUInfo() {
	CPUInfo cpu_info;
	uint64_t freq;
	int cores;
	size_t freq_size = sizeof(freq);
	size_t cores_size = sizeof(cores);
	char cpu_name [256];
	size_t name_size = 256;
	uint64_t cache;
	size_t cache_size = sizeof(cache);
	sysctlbyname("hw.cpufrequency", &freq, &freq_size, NULL, 0);
	sysctlbyname("hw.physicalcpu", &cores, &cores_size, NULL, 0);
	sysctlbyname("machdep.cpu.brand_string", &cpu_name, &name_size, NULL, 0);
	sysctlbyname("hw.l2cachesize", &cache, &cache_size, NULL, 0);
	
	cpu_info.cores = cores;
	cpu_info.cache_size = cache;		
	cpu_info.name = string(cpu_name);
	cpu_info.frequency = freq;
	
	return cpu_info;
}

