#include <windows.h>
#include "fileinfo.h"
#include <iostream>
#include <string>
#include <ctime>


using namespace std;


FileInfo getFileInfo(string file_name) {
	WIN32_FILE_ATTRIBUTE_DATA fInfo;
	GetFileAttributesEx(file_name.c_str(), GetFileExInfoStandard, &fInfo);
	FileInfo file_info;
	file_info.name = file_name;
	std::cout << "High date " << fInfo.ftCreationTime.dwLowDateTime << " Low date " << fInfo.ftCreationTime.dwHighDateTime << std::endl;
	std::cout << "High size " << fInfo.nFileSizeHigh << " low size " << fInfo.nFileSizeLow << std::endl;
	std::time_t now_time = std::time(0);
	std::tm current_tm = *(std::localtime(&now_time));
	file_info.size = 256;
	file_info.modification = current_tm;
	file_info.creation = current_tm;
	return file_info;
}

