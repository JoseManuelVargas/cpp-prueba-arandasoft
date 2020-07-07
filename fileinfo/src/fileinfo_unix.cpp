#include "fileinfo.h"
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <ctime>
#include <time.h>


using namespace std;


FileInfo getFileInfo(string file_name) {
	FileInfo file_info;
	file_info.name = file_name;
	struct stat file;

	if (stat(file_name.c_str(), &file) != 0) {
		struct tm min_time = {0};
		min_time.tm_year = 0;
		min_time.tm_hour = 0;
		min_time.tm_mday = 1;
		min_time.tm_wday = 0;
		min_time.tm_mon = 0;
		min_time.tm_min = 0;
		min_time.tm_sec = 0;
		file_info.size = -1;
		file_info.creation = min_time;
		file_info.modification = min_time;
		return file_info;
	}
	file_info.size = file.st_size;
	file_info.modification = (*std::localtime(&file.st_mtime));
	file_info.creation = (*std::localtime(&file.st_ctime));
	return file_info;
}

