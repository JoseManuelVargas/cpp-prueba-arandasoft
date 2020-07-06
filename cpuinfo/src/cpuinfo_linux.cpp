#include <iostream>
#include <fstream>
#include <string>
#include "cpuinfo.h"

using namespace std;


CPUInfo getCPUInfo() {
	CPUInfo cpu_info;
	string line;
	ifstream cpu_file("/proc/cpuinfo");
	if (!cpu_file.is_open()) {
		cpu_info.frequency = -1;
		cpu_info.cores = -1;
		cpu_info.name = "NaN";
		cpu_info.cache_size = -1;
		return cpu_info;
	}
	string delimiter = ":";
	bool b_cores = false, b_freq = false, b_cache = false, b_name = false;
	while (getline(cpu_file, line)) {
		if (!b_name && line.find("model name") == 0) {
			cpu_info.name = line.substr(line.find(delimiter)+ 1);
			b_name = true;
		}
		else if (!b_freq && line.find("cpu MHz") == 0) {
			cpu_info.frequency = stol(line.substr(line.find(delimiter) + 1));
			b_freq = true;
		}
		else if (!b_cache && line.find("cache size") == 0) {
			cpu_info.cache_size = stol(line.substr(line.find(delimiter) + 1));
			b_cache = true;
		}
		else if (!b_cores && line.find("cpu cores") == 0) {
			cpu_info.cores = stoi(line.substr(line.find(delimiter) + 1));
			b_cores = true;
		}
	}
	cpu_file.close();
	return cpu_info;
}

