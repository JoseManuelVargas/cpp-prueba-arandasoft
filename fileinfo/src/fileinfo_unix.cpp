#include "fileinfo.h"
#include <iostream>
#include <sys/stat.h>
#include <string>
#include <ctime>

using namespace std;


FileInfo getFileInfo(string file_name) {
	FileInfo file_info;
	file_info.name = file_name;
	struct stat file;

	if (stat(file_name.c_str(), &file) != 0) {
		file_info.size = -1;
		file_info.creation = "";
		file_info.modification = "";
		return file_info;
	}
	file_info.size = file.st_size;
	file_info.modification = ctime(&file.st_mtime);
	file_info.creation = ctime(&file.st_ctime);
	return file_info;
}

