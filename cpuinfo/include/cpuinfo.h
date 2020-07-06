#ifndef CPUINFO_H
#define CPUINFO_H

#include <string>

using std::string;

class CPUInfo {
	public:
		long frequency;
		string name;
		int cores;
		long cache_size;
};

CPUInfo getCPUInfo();


#endif /* CPUINFO_H */

